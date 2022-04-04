#include "BigNgine.h"
#include <windows.h>

#include "behaviours/playerMovement/playerMovement.h"
#include "behaviours/circleCollider/circleCollider.h"
#include "behaviours/targetPlayer/targetPlayer.h"
#include "behaviours/shooting/shooting.h"

void Start()
{
}

void Update([[maybe_unused]] int deltaTime)
{
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char **args)
{
	auto *game = BigNgine::Game::GetInstance();

	auto* gameScene = new BigNgine::Scene(
		[game](BigNgine::Scene* scene) -> void {
			// GAME AREA
			const float gameAreaVerticalMargin = 20.f;
			const float gameAreaHorizontalMargin = 50.f;
			const float gameAreaWidth = 700.f;

			auto* gameArea = new BigNgine::Entity(
				BigNgine::Vector2(gameAreaHorizontalMargin - game->GetWindowWidth() / 2.f, gameAreaVerticalMargin - game->GetWindowHeight() / 2.f),
				0.f,
				BigNgine::Vector2(gameAreaWidth, game->GetWindowHeight() - 2 * gameAreaVerticalMargin)
			);

			gameArea->SetDepth(.2f);

			auto* gameAreaRenderer = new BigNgine::ShaderRendererBehaviour();

			// TODO: Add a game background shader
			gameAreaRenderer->SetFragShader(FileSystem::LoadFile("assets/shaders/frag/sky.glsl"));

			gameArea->AddBehaviour(gameAreaRenderer);

			scene->AddEntity(gameArea);

			// BULLET
			auto* bullet = new BigNgine::Entity(
				BigNgine::Vector2(-200.f, -300.f),
				180.f,
				BigNgine::Vector2(20.f, 20.f)
			);

			bullet->SetDepth(-.1f);

			auto* bulletRenderer = new BigNgine::TextureRendererBehaviour();

			bulletRenderer->AddTexture("./assets/img/bullet1.png");

			bullet->AddBehaviour(bulletRenderer);
			bullet->AddBehaviour(new Touhou::CircleColliderBehaviour());
			auto* playerRenderer = new BigNgine::TextureRendererBehaviour();
			scene->AddEntity(bullet);

			// PLAYER
			auto* player = new BigNgine::Entity(
				BigNgine::Vector2(-200.f, 0.f),
				0.f,
				BigNgine::Vector2(100.f, 100.f)
			);
			auto* playerCollider = new BigNgine::Entity(
				BigNgine::Vector2(-200.f, 0.f),
				0.f,
				BigNgine::Vector2(40.f, 40.f)
			);
			player->SetDepth(0.f);


			bullet->AddBehaviour(new Touhou::BulletBehaviour(BigNgine::Vector2(0.f, 0.f)));
			bullet->AddBehaviour(new Touhou::TargetPlayerBehaviour(playerCollider, 0.5f, 500));

			playerRenderer->AddTexture("./assets/img/mariss.png");

			player->AddBehaviour(new BigNgine::FollowBehaviour(playerCollider, player->size/-2.));
			player->AddBehaviour(playerRenderer);
			player->AddBehaviour(new Touhou::ShootingBehaviour(gameArea));

			auto* playerColliderBehaviour = new Touhou::CircleColliderBehaviour();

			playerCollider->AddBehaviour(new Touhou::PlayerMovement(gameArea));
			playerCollider->AddBehaviour(playerColliderBehaviour);

			scene->AddEntity(playerCollider);
			scene->AddEntity(player);

			// DEBUGGER
			auto* debugger = new BigNgine::Entity(
				BigNgine::Vector2(850., 100.),
				0.,
				BigNgine::Vector2(0.,0.)
			);
			
			auto* debuggerRenderer = new BigNgine::TextRendererBehaviour();
			debugger->AddBehaviour(debuggerRenderer);
			debuggerRenderer->SetFontSize(24);
			debuggerRenderer->SetText("no");
			scene->AddEntity(debugger);

			playerColliderBehaviour->SetCallback([debuggerRenderer](Touhou::CircleColliderBehaviour* collider) {
				debuggerRenderer->SetText("yes");
			});
		},
		[](BigNgine::Scene* scene, int deltaTime) -> void {

		}
	);
	
	int option = 0;
	BigNgine::TextRendererBehaviour* menuRenderer;
	auto* MainMenu = new BigNgine::Scene(
		[&option, &menuRenderer, gameScene, game](BigNgine::Scene* scene) -> void {
			// TITLE
			auto* title = new BigNgine::Entity(
				BigNgine::Vector2(0.f, 0.f),
				0.f,
				BigNgine::Vector2(0.f, 0.f)
			);

			auto* titleRenderer = new BigNgine::TextRendererBehaviour();
			title->AddBehaviour(titleRenderer);
			titleRenderer->SetFontSize(24);
			titleRenderer->SetMarginBottom(12);
			titleRenderer->SetText("Touhou\nThe Kerfuffle\nof\nThe Lackadaisical\nRagamuffin");
			scene->AddEntity(title);

			// MENU
			auto* menu = new BigNgine::Entity(
				BigNgine::Vector2(100.f, 290.f),
				0.f,
				BigNgine::Vector2(0.f, 0.f)
			);

			menuRenderer = new BigNgine::TextRendererBehaviour();
			menu->AddBehaviour(menuRenderer);
			menuRenderer->SetFontSize(24);
			menuRenderer->SetMarginBottom(72);
			menuRenderer->SetText(" Start\n Exit");
			scene->AddEntity(menu);


			scene->AddCallback(new Input::Callback([&option, gameScene, game](int key, int, int) -> void {
				switch (key) {
					case BIGNGINE_KEY_UP:
						option = abs((option - 1)%2);
						break;
					case BIGNGINE_KEY_DOWN:
						option = abs((option + 1)%2);
						break;
					case BIGNGINE_KEY_Z:
						if(option == 0)
							game->SetActiveScene(gameScene);
						else if (option == 1)
							game->Stop();
						break;
					default:
						return;
				}
			}));


			auto* chimata = new BigNgine::Entity(
				BigNgine::Vector2(100.f, -130.f),
				0.f,
				BigNgine::Vector2(305.f, 447.f)
			);
			chimata->SetDepth(0.0f);
			auto* chimataRenderer = new BigNgine::TextureRendererBehaviour();
			chimata->AddBehaviour(chimataRenderer);
			chimataRenderer->AddTexture("./assets/img/chimata_main_menu.png");
			scene->AddEntity(chimata);

		},
		[game, gameScene, &option, &menuRenderer](BigNgine::Scene* scene, int deltaTime) -> void {
			if(option == 0)
				menuRenderer->SetText(">Start\n Exit");
			else if(option == 1)
				menuRenderer->SetText(" Start\n>Exit");

		}
	);
 
	auto* TitleScreen = new BigNgine::Scene(
		[game](BigNgine::Scene* scene) -> void {
			auto* title = new BigNgine::Entity(
				BigNgine::Vector2(-600.f, -400.f),
				0.f,
				BigNgine::Vector2(1200.f,800.f)
			);
			title->SetDepth(0.0f);
			auto* renderer = new BigNgine::TextureRendererBehaviour();
			renderer->SetFragShader(FileSystem::LoadFile("assets/shaders/frag/logo.glsl"));
			renderer->SetVertShader(FileSystem::LoadFile("assets/shaders/vert/logo.glsl"));
			renderer->AddTexture("./assets/img/logo.png");
			title->AddBehaviour(renderer);

			scene->AddEntity(title);
	
		},
		[game, MainMenu](BigNgine::Scene* scene, int deltaTime) -> void {
			if(scene->GetActiveTime() >= 3500 || Input::Get(BIGNGINE_KEY_SPACE)) {
				game->SetActiveScene(MainMenu);
			}
		}
	);

	auto* load = new BigNgine::Scene(
		[](BigNgine::Scene* scene) -> void {

		},
		[game, TitleScreen](BigNgine::Scene* scene, int deltaTime) -> void {
			if(scene->GetActiveTime() >= 1000)
				game->SetActiveScene(TitleScreen);
		}
	);
	
	game->ResizeWindow(1200, 800);
	
	game->SetName("Touhou - The Kerfuffle of The Lackadaisical Ragamuffin");
	
	// TODO: Add a custom icon
	game->SetIcon("assets/icon/icon.png");
	
	Logger::Success("Starting game.");
	
	game->Start(load, Start, Update);
	
	return 0;
}	 

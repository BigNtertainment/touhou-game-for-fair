#include "BigNgine.h"
#include <windows.h>

#include "behaviours/enemy/enemy.h"
#include "behaviours/circleCollider/circleCollider.h"
#include "other/createPlayer/createPlayer.h"
#include "other/createEnemy/createEnemy.h"
#include "other/createEnemyBullet/createEnemyBullet.h"
#include "behaviours/targetPlayer/targetPlayer.h"
#include "behaviours/shooting/shooting.h"
#include "behaviours/enemyMovement/enemyMovement.h"
#include "other/gameStatus/gameStatus.h"

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
			Logger::Log("Starting game");

			Touhou::GameStatus::running = true;

			// GAME AREA
			const float gameAreaVerticalMargin = 20.f;
			const float gameAreaHorizontalMargin = 50.f;
			const float gameAreaWidth = 700.f;

			Logger::Log("Creating game area");

			auto* gameArea = new BigNgine::Entity(
				BigNgine::Vector2(gameAreaHorizontalMargin - game->GetWindowWidth() / 2.f, gameAreaVerticalMargin - game->GetWindowHeight() / 2.f),
				0.f,
				BigNgine::Vector2(gameAreaWidth, game->GetWindowHeight() - 2 * gameAreaVerticalMargin)
			);

			gameArea->SetDepth(.2f);

			gameArea->tag = "GameArea";

			auto* gameAreaRenderer = new BigNgine::ShaderRendererBehaviour();

			gameAreaRenderer->SetFragShader(FileSystem::LoadFile("assets/shaders/frag/sky.glsl"));

			gameArea->AddBehaviour(gameAreaRenderer);

			scene->AddEntity(gameArea);

			Logger::Success("Created game area");

			// PLAYER
			Logger::Log("Creating player");
			BigNgine::Entity* player = Touhou::CreatePlayer(scene, gameArea);
			Logger::Success("Created player");

			// DUMMY ENEMY
			Logger::Log("Creating dummy enemy");
			Touhou::CreateSmallEnemy(
				scene,
				gameArea,
				player,
				Touhou::ComeAndGo(
					BigNgine::Vector2(0.3f, 0.3f),
					0.2f,
					5.f
				),
				{
					2, 1, 1
				}
			);
			Logger::Log("Created dummy enemy");

			// LOSE MENU
			auto* loseMenu = new BigNgine::Entity(
				BigNgine::Vector2(game->GetWindowWidth() - 500.f, game->GetWindowHeight()) / 2.f,
				0.f,
				BigNgine::Vector2(0.f, 0.f)
			);

			loseMenu->SetDepth(.1f);

			loseMenu->tag = "LoseMenu";

			loseMenu->SetActive(false);

			BigNgine::TextRendererBehaviour* loseMenuText = new BigNgine::TextRendererBehaviour();

			loseMenuText->SetText("You lose! Press 'z' to go to main menu.");

			loseMenuText->SetFontSize(32);

			loseMenu->AddBehaviour((BigNgine::Behaviour*)loseMenuText);

			scene->AddEntity(loseMenu);

			Touhou::GameStatus::loseMenu = loseMenu;

			Logger::Success("Game started");
		},
		[](BigNgine::Scene*, int) -> void {
			
		}
	);
	
	int option = 0;
	BigNgine::TextRendererBehaviour* menuRenderer;
	auto* MainMenu = new BigNgine::Scene(
		[&option, &menuRenderer, gameScene, game](BigNgine::Scene* scene) -> void {
			Logger::Log("loading main menu");

			// TITLE
			auto* title = new BigNgine::Entity(
				BigNgine::Vector2(0.f, 0.f),
				0.f,
				BigNgine::Vector2(0.f, 0.f)
			);

			auto* titleRenderer = new BigNgine::TextRendererBehaviour();
			title->AddBehaviour((BigNgine::Behaviour*)titleRenderer);
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
			menu->AddBehaviour((BigNgine::Behaviour*)menuRenderer);
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
			chimata->AddBehaviour((BigNgine::Behaviour*)chimataRenderer);
			chimataRenderer->AddTexture("./assets/img/chimata_main_menu.png");

			scene->AddEntity(chimata);

			Logger::Success("Main menu loaded!");
		},
		[gameScene, &option, &menuRenderer](BigNgine::Scene*, int) -> void {
			if(option == 0)
				menuRenderer->SetText(">Start\n Exit");
			else if(option == 1)
				menuRenderer->SetText(" Start\n>Exit");

		}
	);

	Touhou::GameStatus::mainMenu = MainMenu;

	auto* TitleScreen = new BigNgine::Scene(
		[](BigNgine::Scene* scene) -> void {
			Logger::Log("Second scene Loading...");
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
			Logger::Success("second sceen loaded");
		},
		[game, MainMenu](BigNgine::Scene* scene, int) -> void {
			Logger::Log("Second scene running...");
			if(scene->GetActiveTime() >= 3500 || Input::Get(BIGNGINE_KEY_SPACE)) {
				game->SetActiveScene(MainMenu);
			}
		}
	);

	auto* load = new BigNgine::Scene(
		[](BigNgine::Scene*) -> void {
			Logger::Log("First scene Loading...");
			Logger::Success("first sceen loaded");
		},
		[game, TitleScreen](BigNgine::Scene* scene, int) -> void {
			if(scene->GetActiveTime() >= 1000)
				game->SetActiveScene(TitleScreen);
		}
	);
	
	game->ResizeWindow(1200, 800);
	
	game->SetName("Touhou - The Kerfuffle of The Lackadaisical Ragamuffin");
	
	game->SetIcon("assets/icon/icon.png");
	
	Logger::Success("Starting game.");
	
	game->Start(load, Start, Update);
	
	return 0;
}	 

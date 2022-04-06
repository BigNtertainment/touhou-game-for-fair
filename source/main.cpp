#include "BigNgine.h"
#include <windows.h>

#include "behaviours/enemy/enemy.h"
#include "behaviours/circleCollider/circleCollider.h"
#include "other/createPlayer/createPlayer.h"
#include "other/createEnemy/createEnemy.h"
#include "behaviours/targetPlayer/targetPlayer.h"
#include "behaviours/shooting/shooting.h"
#include "behaviours/enemyMovement/enemyMovement.h"

void Start()
{
}

void Update([[maybe_unused]] int deltaTime)
{
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char **args)
{
	auto game = BigNgine::Game::GetInstance();

	auto gameScene = new BigNgine::Scene(
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

			gameArea->tag = "GameArea";

			auto gameAreaRenderer = new BigNgine::ShaderRendererBehaviour();

			gameAreaRenderer->SetFragShader(FileSystem::LoadFile("assets/shaders/frag/sky.glsl"));

			gameArea->AddBehaviour(gameAreaRenderer);

			scene->AddEntity(gameArea);

			// PLAYER
			Touhou::CreatePlayer(scene, gameArea);

			// DUMMY ENEMY
			Touhou::CreateSmallEnemy(
				scene,
				gameArea,
				Touhou::ComeAndGo(
					gameArea,
					BigNgine::Vector2(0.3f, 0.3f),
					0.2f,
					2.f
				)
			);

			// UI
			auto UI = new BigNgine::Entity(
				BigNgine::Vector2(-600.f, -400.f),
				0.f,
				BigNgine::Vector2(1200.f,800.f)
			);
			UI->SetDepth(0.0f);
			auto UIrenderer = new BigNgine::TextureRendererBehaviour();
			UIrenderer->SetVertShader(FileSystem::LoadFile("assets/shaders/vert/logo.glsl"));
			UIrenderer->AddTexture("./assets/img/UI.png");
			UI->AddBehaviour(UIrenderer);
			scene->AddEntity(UI);
			
//			FIXME(tmyon): when entity is destroyed Ui stops rendering for one frame
			auto empty = new BigNgine::Entity();
			scene->AddEntity(empty);

		},
		[](BigNgine::Scene*, int) -> void {
			
		}
	);
	
	int option = 0;
	BigNgine::TextRendererBehaviour* exitRenderer;
	BigNgine::TextRendererBehaviour* startRenderer;
	auto MainMenu = new BigNgine::Scene(
		[&option, &exitRenderer, &startRenderer, gameScene, game](BigNgine::Scene* scene) -> void {
			

			// BACKGROUND
			auto background = new BigNgine::Entity(
				BigNgine::Vector2(-600.f, -400.f),
				0.f,
				BigNgine::Vector2(1200.f,800.f)
			);
			background->SetDepth(-1.f);
			auto backRenderer = new BigNgine::TextureRendererBehaviour();
			backRenderer->SetVertShader(FileSystem::LoadFile("assets/shaders/vert/logo.glsl"));
			backRenderer->AddTexture("./assets/img/back.jpg");
			background->AddBehaviour(backRenderer);
			scene->AddEntity(background);
			
			
			
			// TITLE
			auto title = new BigNgine::Entity(
				BigNgine::Vector2(100.f, 20.f),
				0.f,
				BigNgine::Vector2(0.f, 0.f)
			);
			
			auto titleRenderer = new BigNgine::TextRendererBehaviour();
			title->AddBehaviour((BigNgine::Behaviour*)titleRenderer);
			titleRenderer->SetFragShader(FileSystem::LoadFile("assets/shaders/frag/MenuText.glsl"));
			titleRenderer->SetFont("assets/fonts/UbuntuCondensed-Regular.ttf");
			titleRenderer->SetFontSize(46);
			titleRenderer->SetMarginBottom(12);
			titleRenderer->SetText("Touhou");
			scene->AddEntity(title);

			// SUBTITLE
			auto subtitle = new BigNgine::Entity(
				BigNgine::Vector2(106.f, 66.f),
				0.f,
				BigNgine::Vector2(0.f, 0.f)
			);

			auto subtitleRenderer = new BigNgine::TextRendererBehaviour();
			subtitle->AddBehaviour((BigNgine::Behaviour*)subtitleRenderer);
			subtitleRenderer->SetFragShader(FileSystem::LoadFile("assets/shaders/frag/MenuText.glsl"));
			subtitleRenderer->SetFont("assets/fonts/UbuntuCondensed-Regular.ttf");
			subtitleRenderer->SetFontSize(16);
			subtitleRenderer->SetMarginBottom(12);
			subtitleRenderer->SetText("The Kerfuffle of The Lackadaisical Ragamuffin");
			scene->AddEntity(subtitle);


			// MENU
			auto start = new BigNgine::Entity(
				BigNgine::Vector2(100.f, 290.f),
				0.f,
				BigNgine::Vector2(0.f, 0.f)
			);

			startRenderer = new BigNgine::TextRendererBehaviour();
			start->AddBehaviour((BigNgine::Behaviour*)startRenderer);
			startRenderer->SetFragShader(FileSystem::LoadFile("assets/shaders/frag/MenuText.glsl"));
			startRenderer->SetFont("assets/fonts/MeriendaOne-Regular.ttf");
			startRenderer->SetFontSize(24);
			startRenderer->SetText("Start");
			scene->AddEntity(start);

			auto exit = new BigNgine::Entity(
				BigNgine::Vector2(100.f, 386.f),
				0.f,
				BigNgine::Vector2(0.f, 0.f)
			);

			exitRenderer = new BigNgine::TextRendererBehaviour();
			exit->AddBehaviour((BigNgine::Behaviour*)exitRenderer);
			exitRenderer->SetFragShader(FileSystem::LoadFile("assets/shaders/frag/MenuText.glsl"));
			exitRenderer->SetFont("assets/fonts/MeriendaOne-Regular.ttf");
			exitRenderer->SetFontSize(24);
			exitRenderer->SetText("Exit");
			scene->AddEntity(exit);


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

			// CHIMATA SPRITE
			auto chimata = new BigNgine::Entity(
				BigNgine::Vector2(100.f, -130.f),
				0.f,
				BigNgine::Vector2(305.f, 447.f)
			);
			chimata->SetDepth(0.0f);
			auto chimataRenderer = new BigNgine::TextureRendererBehaviour();
			chimata->AddBehaviour((BigNgine::Behaviour*)chimataRenderer);
			chimataRenderer->AddTexture("./assets/img/chimata_main_menu.png");
			scene->AddEntity(chimata);



			auto discleaimer = new BigNgine::Entity(
				BigNgine::Vector2(5.f, 781.f),
				0.f,
				BigNgine::Vector2(0.f, 0.f)
			);
			title->SetDepth(0.0f);

			auto discleaimerRenderer = new BigNgine::TextRendererBehaviour();
			discleaimer->AddBehaviour((BigNgine::Behaviour*)discleaimerRenderer);
			discleaimerRenderer->SetText("This game is based off of Touhou Project by Team Shanghai Alice.");
			scene->AddEntity(discleaimer);

		},
		[game, gameScene, &option, &startRenderer, &exitRenderer](BigNgine::Scene* scene, int deltaTime) -> void {
			if(option == 0){
				startRenderer->rainbow = 1;
				exitRenderer->rainbow = 0;
			} else if(option == 1) {
				startRenderer->rainbow = 0;
				exitRenderer->rainbow = 1;
			}

		}
	);
 
	auto TitleScreen = new BigNgine::Scene(
		[game](BigNgine::Scene* scene) -> void {
			Logger::Log("Second scene Loading...");
			auto title = new BigNgine::Entity(
				BigNgine::Vector2(-600.f, -400.f),
				0.f,
				BigNgine::Vector2(1200.f,800.f)
			);
			title->SetDepth(0.0f);
			auto renderer = new BigNgine::TextureRendererBehaviour();
			renderer->SetFragShader(FileSystem::LoadFile("assets/shaders/frag/logo.glsl"));
			renderer->SetVertShader(FileSystem::LoadFile("assets/shaders/vert/logo.glsl"));
			renderer->AddTexture("./assets/img/logo.png");
			title->AddBehaviour(renderer);
			scene->AddEntity(title);

			Logger::Success("second sceen loaded");
		},
		[game, MainMenu](BigNgine::Scene* scene, int deltaTime) -> void {
			Logger::Log("Second scene running...");
			if(scene->GetActiveTime() >= 3500 || Input::Get(BIGNGINE_KEY_SPACE)) {
				game->SetActiveScene(MainMenu);
			}
		}
	);

	auto load = new BigNgine::Scene(
		[](BigNgine::Scene* scene) -> void {
			Logger::Log("First scene Loading...");
			Logger::Success("first sceen loaded");
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

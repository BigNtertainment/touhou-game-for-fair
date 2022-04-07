#include "BigNgine.h"
#include <windows.h>

#include "behaviours/enemy/enemy.h"
#include "behaviours/circleCollider/circleCollider.h"
#include "other/createPlayer/createPlayer.h"
#include "other/createEnemy/createEnemy.h"
#include "other/score/score.h"
#include "other/createEnemyBullet/createEnemyBullet.h"
#include "behaviours/targetPlayer/targetPlayer.h"
#include "behaviours/shooting/shooting.h"
#include "behaviours/enemyMovement/enemyMovement.h"
#include "other/gameStatus/gameStatus.h"
#include "other/enemyWave/enemyWave.h"

void Start()
{
}

void Update([[maybe_unused]] int deltaTime)
{
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char **args)
{
	auto game = BigNgine::Game::GetInstance();

	auto ScoreRenderer = new BigNgine::TextRendererBehaviour();
	auto hitBoxRenderer = new BigNgine::TextureRendererBehaviour();

	BigNgine::Entity* gameArea = nullptr;
	BigNgine::Entity* player = nullptr;

	auto gameScene = new BigNgine::Scene(
		[game, &ScoreRenderer, &gameArea, &player, &hitBoxRenderer](BigNgine::Scene* scene) -> void {
			Logger::Log("Starting game");

			Touhou::GameStatus::running = true;

			Logger::Log("a");

			Touhou::Score::points = 0;

			Logger::Log("b");

			// GAME AREA
			const float gameAreaVerticalMargin = 20.f;
			const float gameAreaHorizontalMargin = 50.f;
			const float gameAreaWidth = 700.f;

			Logger::Log("Creating game area");

			gameArea = new BigNgine::Entity(
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

			Logger::Success("Created game area");

			// this prevents player from stuttering 
			// i hate this 
			auto empty = new BigNgine::Entity();
			scene->AddEntity(empty);

			// PLAYER
			Logger::Log("Creating player");

			player = Touhou::CreatePlayer(scene, gameArea);

			Logger::Success("Created player");

			BigNgine::Entity* playerHitbox = new BigNgine::Entity(
				player->position - player->size / 2.f,
				0.f,
				player->size
			);

			playerHitbox->AddBehaviour(new BigNgine::FollowBehaviour(player));

			hitBoxRenderer->AddTexture("assets/icon/icon.png");

			playerHitbox->AddBehaviour((BigNgine::Behaviour*)hitBoxRenderer);

			scene->AddEntity(playerHitbox);

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

			UI->AddBehaviour((BigNgine::Behaviour*)UIrenderer);

			scene->AddEntity(UI);

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

			loseMenuText->SetText("Game over! Press 'z' to go to main menu.");

			loseMenuText->SetFontSize(32);

			loseMenu->AddBehaviour((BigNgine::Behaviour*)loseMenuText);

			scene->AddEntity(loseMenu);

			Touhou::GameStatus::loseMenu = loseMenu;

			// SCORE
			auto Score = new BigNgine::Entity(
				BigNgine::Vector2(790.f, 80.f),
				0.f,
				BigNgine::Vector2(0.f, 0.f)
			);

			Score->SetDepth(0.0f);

			ScoreRenderer = new BigNgine::TextRendererBehaviour();

			ScoreRenderer->SetFont("assets/fonts/MeriendaOne-Regular.ttf");
			ScoreRenderer->SetFontSize(24);
			ScoreRenderer->SetText("Score:");

			Score->AddBehaviour((BigNgine::Behaviour*)ScoreRenderer);

			scene->AddEntity(Score);

			Touhou::EnemyWave::Start();

			Logger::Success("Game started");
		},
		[&ScoreRenderer](BigNgine::Scene*, int deltaTime) -> void {
			ScoreRenderer->SetText("Score: " + std::to_string(Touhou::Score::points));
			hitBoxRenderer->SetActive(Input::Get(BIGNGINE_KEY_LEFT_SHIFT));

			if(Touhou::GameStatus::running)
				Touhou::EnemyWave::Update(deltaTime);
		}
	);

	// ENEMY WAVES
	auto EnemyWave = new Touhou::EnemyWave(gameScene, [&gameArea, &player](BigNgine::Scene* scene) -> void {
		Touhou::CreateSmallEnemy(
			scene,
			gameArea,
			player,
			Touhou::ComeAndGo(
				BigNgine::Vector2(0.4f, 0.3f),
				0.2f,
				3.f
			),
			{ 1, 1, 1 }
		);

		Touhou::CreateSmallEnemy(
			scene,
			gameArea,
			player,
			Touhou::ComeAndGo(
				BigNgine::Vector2(0.6f, 0.3f),
				0.2f,
				3.f
			),
			{ 1, 1, 1 }
		);
	}, 5.f);

	auto EnemyWave2 = new Touhou::EnemyWave(gameScene, [&gameArea, &player](BigNgine::Scene* scene) -> void {
		Touhou::CreateSmallEnemy(
			scene,
			gameArea,
			player,
			Touhou::ComeAndGo(
				BigNgine::Vector2(0.3f, 0.3f),
				0.2f,
				3.f
			),
			{ 1, 1, 1 }
		);
		
		Touhou::CreateSmallEnemy(
			scene,
			gameArea,
			player,
			Touhou::ComeAndGo(
				BigNgine::Vector2(0.5f, 0.5f),
				0.2f,
				3.f
			),
			{ 1, 1, 1 }
		);

		Touhou::CreateSmallEnemy(
			scene,
			gameArea,
			player,
			Touhou::ComeAndGo(
				BigNgine::Vector2(0.7f, 0.3f),
				0.2f,
				3.f
			),
			{ 1, 1, 1 }
		);
	}, 3.f);

	auto EnemyWave3 = new Touhou::EnemyWave(gameScene, [&gameArea, &player](BigNgine::Scene* scene) -> void {
		Touhou::CreateSmallEnemy(
			scene,
			gameArea,
			player,
			[&gameArea](int time) -> BigNgine::Vector2 {
				float realTime = time / 1000.f;

				return BigNgine::Vector2((sin(realTime) + 2.f) / 4.f, (100 * realTime + 2.f) / gameArea->size.y);
			},
			{ 1, 1, 1, 1 }
		);

		Touhou::CreateSmallEnemy(
			scene,
			gameArea,
			player,
			[&gameArea](int time) -> BigNgine::Vector2 {
				float realTime = time / 1000.f;

				return BigNgine::Vector2(1.f - (sin(realTime) + 2.f) / 4.f, (100 * realTime + 2.f) / gameArea->size.y);
			},
			{ 1, 1, 1, 1 }
		);
	}, 4.f);

	int option = 0;
	BigNgine::TextRendererBehaviour* menuRenderer;
	BigNgine::TextRendererBehaviour* exitRenderer;
	BigNgine::TextRendererBehaviour* startRenderer;
	auto MainMenu = new BigNgine::Scene(
		[&option, &menuRenderer, &exitRenderer, &startRenderer, gameScene, game](BigNgine::Scene* scene) -> void {
			Logger::Log("loading main menu");

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
			background->AddBehaviour((BigNgine::Behaviour*)backRenderer);
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

			auto disclaimer = new BigNgine::Entity(
				BigNgine::Vector2(5.f, 781.f),
				0.f,
				BigNgine::Vector2(0.f, 0.f)
			);

			disclaimer->SetDepth(0.0f);

			auto discleaimerRenderer = new BigNgine::TextRendererBehaviour();

			disclaimer->AddBehaviour((BigNgine::Behaviour*)discleaimerRenderer);
			discleaimerRenderer->SetText("This game is based off of Touhou Project by Team Shanghai Alice.");

			scene->AddEntity(disclaimer);
		},
		[&option, &startRenderer, &exitRenderer](BigNgine::Scene* scene, int deltaTime) -> void {
			if(option == 0){
				startRenderer->rainbow = 1;
				exitRenderer->rainbow = 0;
			} else if(option == 1) {
				startRenderer->rainbow = 0;
				exitRenderer->rainbow = 1;
			}
		}
	);

	Touhou::GameStatus::mainMenu = MainMenu;

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
		[game, MainMenu](BigNgine::Scene* scene, int) -> void {
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

	// delete EnemyWave, EnemyWave2, EnemyWave3;

	return 0;
}	 

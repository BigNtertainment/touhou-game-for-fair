#include "BigNgine.h"
#include <windows.h>

#include "behaviours/enemy/enemy.h"
#include "behaviours/circleCollider/circleCollider.h"
#include "other/createPlayer/createPlayer.h"

void Start()
{
}

void Update([[maybe_unused]] int deltaTime)
{
}

// FIXME: Game crashes on exit

int main([[maybe_unused]] int argc, [[maybe_unused]] char **args)
{
	BigNgine::Game *game = BigNgine::Game::GetInstance();

	BigNgine::Scene* scene = new BigNgine::Scene(
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

			gameAreaRenderer->SetFragShader(FileSystem::LoadFile("assets/shaders/frag/sky.glsl"));

			gameArea->AddBehaviour(gameAreaRenderer);

			scene->AddEntity(gameArea);

			// PLAYER
			Touhou::CreatePlayer(scene, gameArea);

			// DUMMY ENEMY
			BigNgine::Entity* dummy = new BigNgine::Entity(
				BigNgine::Vector2(
					gameAreaHorizontalMargin + gameAreaWidth / 2.f - game->GetWindowWidth() / 2.f,
					gameAreaVerticalMargin + 20.f - game->GetWindowHeight() / 2.f
				),
				0.f,
				BigNgine::Vector2(100.f, 100.f)
			);

			dummy->SetDepth(.1f);

			dummy->tag = "Enemy";

			BigNgine::TextureRendererBehaviour* dummyRenderer = new BigNgine::TextureRendererBehaviour();

			dummyRenderer->name = "dummy_renderer";

			dummyRenderer->AddTexture("./assets/img/mariss.png");

			dummy->AddBehaviour(dummyRenderer);
			dummy->AddBehaviour(new Touhou::EnemyBehaviour());
			dummy->AddBehaviour(new Touhou::CircleColliderBehaviour());

			scene->AddEntity(dummy);
		},
		[](BigNgine::Scene* scene, int deltaTime) -> void {
			
		}
	);
	
	game->ResizeWindow(1200, 800);
	
	game->SetName("Touhou - The Kerfuffle of The Lackadaisical Ragamuffin");
	
	// TODO: Add a custom icon
	game->SetIcon("assets/icon/icon.png");
	
	Logger::Success("Starting game.");
	// TODO: add loading screen 
	game->Start(scene, Start, Update);
	
	return 0;
}	
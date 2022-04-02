#include "BigNgine.h"
#include <windows.h>

#include "behaviours/playerMovement/playerMovement.h"
#include "behaviours/shooting/shooting.h"

void Start()
{
}

void Update([[maybe_unused]] int deltaTime)
{
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char **args)
{
	BigNgine::Game *game = BigNgine::Game::GetInstance();

	BigNgine::Scene* scene = new BigNgine::Scene(
		[game](BigNgine::Scene* scene) -> void {
			// GAME AREA
			const float gameAreaVerticalMargin = 20.f;
			const float gameAreaHorizontalMargin = 20.f;

			auto* gameArea = new BigNgine::Entity(
				BigNgine::Vector2(gameAreaVerticalMargin - game->GetWindowWidth() / 2.f, gameAreaHorizontalMargin - game->GetWindowHeight() / 2.f),
				0.f,
				BigNgine::Vector2(500.f, game->GetWindowHeight() - 2 * gameAreaVerticalMargin)
			);

			gameArea->SetDepth(0.1f);

			auto* gameAreaRenderer = new BigNgine::ShaderRendererBehaviour();

			// TODO: Add a game background shader
			gameAreaRenderer->SetFragShader(FileSystem::LoadFile("assets/shaders/frag/standard.glsl"));

			gameArea->AddBehaviour(gameAreaRenderer);

			scene->AddEntity(gameArea);

			// PLAYER
			BigNgine::Entity* player = new BigNgine::Entity(
				BigNgine::Vector2(0.f, 0.f),
				0.f,
				BigNgine::Vector2(100.f, 100.f)
			);

			player->SetDepth(0.f);

			auto* playerRenderer = new BigNgine::TextureRendererBehaviour();

			playerRenderer->AddTexture("./assets/img/mariss.png");

			player->AddBehaviour(playerRenderer);
			player->AddBehaviour(new Touhou::PlayerMovement(gameArea));
			player->AddBehaviour(new Touhou::ShootingBehaviour());

			scene->AddEntity(player);
		},
		[](BigNgine::Scene* scene, int deltaTime) -> void {

		}
	);
	
	game->ResizeWindow(1200, 800);
	
	game->SetName("Touhou - The Kerfuffle of The Lackadaisical Ragamuffin");
	
	// TODO: Add a custom icon
	game->SetIcon("assets/icon/icon.png");
	
	Logger::Success("Starting game.");
	
	game->Start(scene, []() -> void {}, [](int) -> void {});
	
	return 0;
}
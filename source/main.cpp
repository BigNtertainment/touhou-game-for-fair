#include "BigNgine.h"
#include <windows.h>

#include "behaviours/playerMovement/playerMovement.h"
#include "behaviours/circleCollider/circleCollider.h"
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
			BigNgine::Entity* bullet = new BigNgine::Entity(
				BigNgine::Vector2(-200.f, 0.f),
				45.f,
				BigNgine::Vector2(20.f, 20.f)
			);

			bullet->SetDepth(-.1f);

			auto* bulletRenderer = new BigNgine::TextureRendererBehaviour();

			bulletRenderer->AddTexture("./assets/icon/icon.png");

			bullet->AddBehaviour(bulletRenderer);
			bullet->AddBehaviour(new Touhou::CircleColliderBehaviour());
			scene->AddEntity(bullet);

			// PLAYER
			auto* player = new BigNgine::Entity(
				BigNgine::Vector2(0.f, 0.f),
				0.f,
				BigNgine::Vector2(100.f, 100.f)
			);
			auto* playerCollider = new BigNgine::Entity(
				BigNgine::Vector2(0.f, 0.f),
				0.f,
				BigNgine::Vector2(40.f, 40.f)
			);
			playerCollider->SetDepth(0.f);
			player->SetDepth(0.f);

			auto* playerRenderer = new BigNgine::TextureRendererBehaviour();

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
	
	game->ResizeWindow(1200, 800);
	
	game->SetName("Touhou - The Kerfuffle of The Lackadaisical Ragamuffin");
	
	// TODO: Add a custom icon
	game->SetIcon("assets/icon/icon.png");
	
	Logger::Success("Starting game.");
	// TODO: add loading screen 
	game->Start(scene, Start, Update);
	
	return 0;
}	
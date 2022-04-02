#include "BigNgine.h"
#include <windows.h>

void Start()
{
}

void Update([[maybe_unused]] int deltaTime)
{
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char **args)
{
	BigNgine::Scene* scene = new BigNgine::Scene(
		[](BigNgine::Scene* scene) {
			BigNgine::Entity* entity = new BigNgine::Entity(
				BigNgine::Vector2(0.f, 0.f),
				0.f,
				BigNgine::Vector2(100.f, 100.f)
			);

			entity->SetDepth(0.f);

			auto* renderer = new BigNgine::TextureRendererBehaviour();

			renderer->AddTexture("./assets/img/mariss.png");

			entity->AddBehaviour(renderer);

			scene->AddEntity(entity);
		},
		[](BigNgine::Scene* scene, int deltaTime) {

		}
	);

	BigNgine::Game *game = BigNgine::Game::GetInstance();
	
	game->ResizeWindow(1200, 800);
	
	game->SetName("BigNgine");
	
	game->SetIcon("assets/icon/icon.png");
	
	Logger::Success("Starting game.");
	
	game->Start(scene, Start, Update);
	
	return 0;
}
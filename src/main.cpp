#include "BigNgine.h"
#include <windows.h>

auto *Scene = new BigNgine::Scene(
		[](BigNgine::Scene *Scene) -> void {
			BigNgine::Entity* entity = new BigNgine::Entity();
			
			BigNgine::TextureRendererBehaviour* renderer = new BigNgine::TextureRendererBehaviour();

			renderer->AddTexture("./assets/textures/mariss.png");

			Scene->AddEntity(entity);
		},
		[](BigNgine::Scene *Scene, int deltaTime)
		{
			
		}
);

void Start()
{
}

void Update([[maybe_unused]] int deltaTime)
{
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char **args)
{
	BigNgine::Game *game = BigNgine::Game::GetInstance();
	
	game->ResizeWindow(1200, 800);
	
	game->SetName("BigNgine");
	
	game->SetIcon("assets/icon/icon.png");
	
	Logger::Success("Starting game.");
	
	game->Start(Scene, Start, Update);
	
	return 0;
}
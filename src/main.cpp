#include "BigNgine.h"
#include <windows.h>

class FunnyBehaviour : public BigNgine::Behaviour
{
public:
	void Start() override {
		Logger::Log("hello");
	}

	void Update(int deltaTime) override {
		parent->position.x += deltaTime / 1000.f;
		Logger::Log(parent->position);
	}
};

auto *Scene = new BigNgine::Scene(
		[](BigNgine::Scene *Scene) -> void {
			Logger::Log(1);

			BigNgine::Entity* entity = new BigNgine::Entity(
				BigNgine::Vector2(0, 0),
				0.f,
				BigNgine::Vector2(100, 100)
			);

			Logger::Log(2);

			BigNgine::TextureRendererBehaviour* renderer = new BigNgine::TextureRendererBehaviour();

			Logger::Log(3);

			renderer->AddTexture("assets/img/mariss.png");

			entity->AddBehaviour(renderer);
			entity->AddBehaviour(new FunnyBehaviour());

			Logger::Log(3);

			Scene->AddEntity(entity);

			Logger::Log(4);
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
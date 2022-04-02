#include <BigNgine.h>

class FunnyBehaviour : public BigNgine::Behaviour {
public:
	void Update(int) override {
		std::cout << "FunnyBehaviour updated" << std::endl;
	}
};

int main() {
	auto* scene = new BigNgine::Scene([](BigNgine::Scene* scene) -> void {
		BigNgine::Entity* entity = new BigNgine::Entity(
			BigNgine::Vector2(100.f, 100.f),
			0.f,
			BigNgine::Vector2(100.f, 100.f)
		);

		entity->SetDepth(0.f);

		BigNgine::TextureRendererBehaviour* renderer = new BigNgine::TextureRendererBehaviour();

		renderer->AddTexture("./assets/img/mariss.png");

		entity->AddBehaviour(renderer);
		entity->AddBehaviour(new FunnyBehaviour());

		scene->AddEntity(entity);
	},[](BigNgine::Scene* scene, int deltaTime) -> void {

	});

	BigNgine::Game* game = BigNgine::Game::GetInstance();

	game->SetName("Touhou 19 - The Kerfuffle of The Lackadaisical Ragamuffin");

	game->ResizeWindow(1280, 720);

	game->Start(scene, []() -> void {}, [](int) -> void {});

	return 0;
}
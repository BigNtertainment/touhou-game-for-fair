#include <BigNgine.h>
#include "math.h"

BigNgine::Vector2 Normalize(BigNgine::Vector2 vector)
{
	float length = sqrt(vector.x * vector.x + vector.y * vector.y);

	if(length == 0)
		return vector;

	return BigNgine::Vector2(vector.x / length, vector.y / length); 
}

class MovementBehaviour : public BigNgine::Behaviour {
public:
	float speed = 400.f;

	void Update(int deltaTime) override {
		auto movementVector = BigNgine::Vector2(
			(float)(Input::Get(BIGNGINE_KEY_D) - Input::Get(BIGNGINE_KEY_A)),
			(float)(Input::Get(BIGNGINE_KEY_S) - Input::Get(BIGNGINE_KEY_W))
		);

		// Normalize the movement vector
		movementVector = Normalize(movementVector);

		parent->position.x += movementVector.x * speed * deltaTime / 1000.f;
		parent->position.y += movementVector.y * speed * deltaTime / 1000.f;
	}
};

int main() {
	BigNgine::Entity* entity;

	auto* scene = new BigNgine::Scene([&entity](BigNgine::Scene* scene) -> void {
		entity = new BigNgine::Entity(
			BigNgine::Vector2(100.f, 100.f),
			0.f,
			BigNgine::Vector2(100.f, 100.f)
		);

		entity->SetDepth(0.f);

		auto* renderer = new BigNgine::ShaderRendererBehaviour();

		renderer->SetFragShader(FileSystem::LoadFile("assets/shaders/frag/standard.glsl"));

		// renderer->AddTexture("./assets/img/mariss.png");

		// renderer->setText("Hello World!");

		entity->AddBehaviour(renderer);
		entity->AddBehaviour(new MovementBehaviour());

		BigNgine::Entity* entity2 = new BigNgine::Entity(
			BigNgine::Vector2(0.f, 0.f),
			0.f,
			BigNgine::Vector2(100.f, 100.f)
		);

		entity2->SetDepth(1.f);

		auto* renderer2 = new BigNgine::TextureRendererBehaviour();

		renderer2->AddTexture("./assets/img/mariss.png");

		entity2->AddBehaviour(renderer2);

		scene->AddEntity(entity);
		scene->AddEntity(entity2);
	}, [&entity](BigNgine::Scene* scene, int deltaTime) -> void {
	});

	BigNgine::Game* game = BigNgine::Game::GetInstance();

	game->ResizeWindow(1200, 800);

	game->SetName("Touhou 19 - The Kerfuffle of The Lackadaisical Ragamuffin");

	game->Start(scene, []() -> void {}, [](int) -> void {});

	return 0;
}
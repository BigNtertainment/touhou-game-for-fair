#include "createEnemy.h"



void Touhou::CreateEnemy(BigNgine::Scene* scene, BigNgine::Entity* gameArea, BigNgine::Vector2 position) {
            BigNgine::Entity* dummy = new BigNgine::Entity(
            position,
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
}
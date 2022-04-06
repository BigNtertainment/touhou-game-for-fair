#include "enemySmall.h"
#include "behaviours/renderer/renderer.h"

BigNgine::Entity* Touhou::EnemySmall::Create(void** args) {
	BigNgine::Entity* gameArea = (BigNgine::Entity*)args[0];

	BigNgine::Entity* enemy = new BigNgine::Entity(
		gameArea->position,
		0.f,
		enemySize
	);

	enemy->SetDepth(0.f);

	enemy->tag = "EnemyModel";

	BigNgine::TextureRendererBehaviour *renderer = new BigNgine::TextureRendererBehaviour();

	renderer->AddTexture("./assets/img/mariss.png");

	enemy->AddBehaviour(renderer);

	return enemy;
}
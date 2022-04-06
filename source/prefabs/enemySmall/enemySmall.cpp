#include "enemySmall.h"

#include "behaviours/renderer/renderer.h"
#include "behaviours/enemyShooting/enemyShooting.h"

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

	enemy->AddBehaviour((BigNgine::Behaviour*)new EnemyShootingBehaviour(
		gameArea,
		(BigNgine::Entity*)args[1],
		*(std::vector<uint16_t>*)args[2]
	));

	return enemy;
}
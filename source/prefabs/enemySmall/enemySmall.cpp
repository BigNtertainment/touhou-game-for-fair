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

	renderer->name = "enemy_Renderer";

	renderer->AddTexture("./assets/img/lobster.png");

	enemy->AddBehaviour(renderer);

	auto shooting = new EnemyShootingBehaviour(
		gameArea,
		(BigNgine::Entity*)args[1],
		*(std::vector<uint16_t>*)args[2]
	);

	shooting->name = "enemy_Shooting";

	enemy->AddBehaviour((BigNgine::Behaviour*)shooting);

	return enemy;
}
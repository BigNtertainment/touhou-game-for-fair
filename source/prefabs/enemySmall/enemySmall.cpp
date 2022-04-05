#include "enemySmall.h"
#include "behaviours/renderer/renderer.h"

BigNgine::Entity* Touhou::EnemySmall::Create(void** args) {
	BigNgine::Entity* gameArea = (BigNgine::Entity*)args[0];

	BigNgine::Entity* enemy = new BigNgine::Entity(
		gameArea->position,
		0.f,
		enemySize
	);

	BigNgine::TextureRendererBehaviour *renderer = new BigNgine::TextureRendererBehaviour();

	Logger::Log(enemyTexture);
	Logger::Log(enemyTexture.c_str());
	renderer->AddTexture(enemyTexture.c_str());

	enemy->AddBehaviour(renderer);

	return enemy;
}
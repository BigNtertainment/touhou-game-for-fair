#include "enemyShooting.h"

#include "other/createEnemyBullet/createEnemyBullet.h"

#include <stdint.h>
#include <corecrt_math.h>
#include <corecrt_math_defines.h>

const BigNgine::Vector2 Touhou::EnemyShootingBehaviour::bulletSize = BigNgine::Vector2(20.f, 20.f);

Touhou::EnemyShootingBehaviour::EnemyShootingBehaviour(
	BigNgine::Entity* gameArea,
	BigNgine::Entity* player,
	std::vector<uint16_t> shotIntervals
) : gameArea(gameArea), player(player), shotIntervals(shotIntervals) {}

void Touhou::EnemyShootingBehaviour::Update(int deltaTime) {
	timer += deltaTime;

	if(intervalIndex < shotIntervals.size()) {
		if(timer >= shotIntervals[intervalIndex] * 1000.f) {
			Shoot();

			timer = 0;
			intervalIndex++;
		}

		return;
	}

	// Delete the behaviour when the enemy won't shoot anymore
	delete this;
}

void Touhou::EnemyShootingBehaviour::Shoot() {
	Logger::Log("shot");

	BigNgine::Vector2 vector = player->position - parent->position;

	CreateEnemyBullet(
		parent->GetParentScene(),
		gameArea,
		player,
		parent->position + BigNgine::Vector2(0.f, parent->size.y / 2.f),
		bulletSize,
		atan(vector.y / vector.x) * 180 / M_PI + 90
	);
}
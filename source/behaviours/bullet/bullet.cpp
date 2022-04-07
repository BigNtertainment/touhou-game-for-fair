#include "bullet.h"

#include "other/gameStatus/gameStatus.h"

Touhou::BulletBehaviour::BulletBehaviour(BigNgine::Vector2 direction) :
	direction(direction) {}

void Touhou::BulletBehaviour::Update(int deltaTime) {
	if(GameStatus::running)
		parent->position = parent->position + direction * deltaTime / 1000.f;
}
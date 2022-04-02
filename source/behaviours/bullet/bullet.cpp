#include "bullet.h"

Touhou::BulletBehaviour::BulletBehaviour(BigNgine::Vector2 direction) :
	direction(direction) {}

void Touhou::BulletBehaviour::Update(int deltaTime) {
	parent->position = parent->position + direction * deltaTime / 1000.f;
}
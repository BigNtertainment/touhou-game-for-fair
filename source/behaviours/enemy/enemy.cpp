#include "enemy.h"

void Touhou::EnemyBehaviour::Damage() {
	health--;

	if (health <= 0) {
		Die();
	}
}

void Touhou::EnemyBehaviour::Die() {
	Logger::Log("Enemy died");

	// It also deletes the behaviour
	delete parent;
}
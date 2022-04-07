#include "enemy.h"

Touhou::EnemyBehaviour::EnemyBehaviour(BigNgine::Entity* _model) : model(_model) {}

void Touhou::EnemyBehaviour::Damage() {
	health--;

	if (health <= 0) {
		Die();
	}
}

void Touhou::EnemyBehaviour::Die() {
	Logger::Log("Enemy died");

	// add points to score
	Score::points += 500;

	// Delete the model
	parent->GetParentScene()->RemoveEntity(model);

	// It also deletes the behaviours
	parent->GetParentScene()->RemoveEntity(parent);
}
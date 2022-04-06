#pragma once

#include "types/scene/scene.h"
#include "types/entity/entity.h"
#include "behaviours/enemyMovement/enemyMovement.h"

namespace Touhou {
	void CreateSmallEnemy(
		BigNgine::Scene* scene,
		BigNgine::Entity* gameArea,
		Touhou::EnemyMovementBehaviour::MovementFunction movementFunction
	);

	Touhou::EnemyMovementBehaviour::MovementFunction ComeAndGo(
		BigNgine::Vector2 target,
		float speed,
		float waitTime
	);
}
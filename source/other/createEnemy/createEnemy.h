#pragma once

#include "types/scene/scene.h"
#include "types/entity/entity.h"
#include "behaviours/enemyMovement/enemyMovement.h"

#include <vector>

namespace Touhou {
	void CreateSmallEnemy(
		BigNgine::Scene* scene,
		BigNgine::Entity* gameArea,
		BigNgine::Entity* player,
		Touhou::EnemyMovementBehaviour::MovementFunction movementFunction,
		std::vector<uint16_t> shotIntervals = std::vector<uint16_t>()
	);

	Touhou::EnemyMovementBehaviour::MovementFunction ComeAndGo(
		BigNgine::Vector2 target,
		float speed,
		float waitTime
	);
}
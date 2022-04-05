#pragma once

#include "types/prefab/prefab.h"
#include <string>

namespace Touhou {
	class EnemySmallCollider : public BigNgine::Prefab {
	public:
		const float enemyColliderSize = 5.f;

		/// @brief Creates a new small enemy collider.
		/// @param void** args Arguments:
		/// - gameArea (BigNgine::Entity*)
        /// - movement function (Touhou::EnemyMovementBehaviour::MovementFunction)
		/// - enemy model (BigNgine::Entity*)
		BigNgine::Entity* Create(void** args) override;
	};
}
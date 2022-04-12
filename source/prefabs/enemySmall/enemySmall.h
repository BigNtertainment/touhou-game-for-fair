#pragma once

#include "types/prefab/prefab.h"
#include <string>

namespace Touhou {
	class EnemySmall : public BigNgine::Prefab {
	public:
		const BigNgine::Vector2 enemySize = BigNgine::Vector2(57.f, 93.f);

		/// @brief Creates a new small enemy.
		/// @param void** args Arguments:
		/// - gameArea (BigNgine::Entity*)
		/// - player (BigNgine::Entity*)
		/// - shot intervals (std::vector<uint16_t>)
		BigNgine::Entity* Create(void** args) override;
	};
}
#pragma once

#include "types/prefab/prefab.h"
#include <string>

namespace Touhou {
	class EnemySmall : public BigNgine::Prefab {
	public:
		const BigNgine::Vector2 enemySize = BigNgine::Vector2(50.f, 50.f);
		// TODO: Change it to an actual enemy texture
		const std::string enemyTexture = "./assets/img/mariss.png";

		/// @brief Creates a new small enemy.
		/// @param void** args Arguments:
		/// - gameArea (BigNgine::Entity*)
		/// - player (BigNgine::Entity*)
		/// - shot intervals (std::vector<uint16_t>)
		BigNgine::Entity* Create(void** args) override;
	};
}
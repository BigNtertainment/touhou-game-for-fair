#pragma once

#include "types/prefab/prefab.h"
#include "types/vector2/vector2.h"

namespace Touhou {
	class EnemyBullet : public BigNgine::Prefab {
	public:
		static const BigNgine::Vector2 bulletSize;
		std::string texturePath = "./assets/img/bullet1.png";

		/// @brief Creates a new player bullet.
		/// @param void** Arguments
		/// - position (BigNgine::Vector2)
		/// - velocity (int)
		/// - player (BigNgine::Entity*)
		/// - gameArea (BigNgine::Entity*)
		BigNgine::Entity* Create(void** args) override;
	};
}
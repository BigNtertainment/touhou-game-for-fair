#pragma once

#include "types/prefab/prefab.h"
#include "types/vector2/vector2.h"

namespace Touhou {
	class EnemyBullet : public BigNgine::Prefab {
	public:
		std::string texturePath = "assets/textures/bullet1.png";

		/// @brief Creates a new player bullet.
		/// @param void** Arguments:
		/// - position (BigNgine::Vector2)
		/// - size (BigNgine::Vector2)
		/// - game area (BigNgine::Entity*)
		BigNgine::Entity* Create(void** args) override;
	};
}
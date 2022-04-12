#pragma once

#include "types/prefab/prefab.h"
#include "types/vector2/vector2.h"

namespace Touhou {
	class PlayerBullet : public BigNgine::Prefab {
	public:
		static const BigNgine::Vector2 bulletSize;

		/// @brief Creates a new player bullet.
		/// @param void** Arguments:
		/// - position (BigNgine::Vector2)
		/// - game area (BigNgine::Entity*)
		BigNgine::Entity* Create(void** args) override;
	};
}
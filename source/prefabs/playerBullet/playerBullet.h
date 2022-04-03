#pragma once

#include "types/prefab/prefab.h"
#include "types/vector2/vector2.h"

namespace Touhou {
	class PlayerBullet : public BigNgine::Prefab {
	public:
		static const BigNgine::Vector2 bulletSize;

		/// @brief Creates a new player bullet.
		/// @param void** First argument is BigNgine::Vector2*, the bullet position, second is BigNgine::Vector2*, the bullet direction, third is BigNgine::Entity*, the bound box for the bullet.
		BigNgine::Entity* Create(void** args) override;
	};
}
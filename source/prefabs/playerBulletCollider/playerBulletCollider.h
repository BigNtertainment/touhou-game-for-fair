#pragma once

#include "types/prefab/prefab.h"

namespace Touhou {
	class PlayerBulletCollider : public BigNgine::Prefab {
	public:
		/// @brief Creates a new small player bullet collider.
		/// @param void** args Arguments:
		/// - model (BigNgine::Entity*)
		/// - movement angle (float)
		/// - movement speed (float)
		BigNgine::Entity* Create(void** args) override;
	};
}
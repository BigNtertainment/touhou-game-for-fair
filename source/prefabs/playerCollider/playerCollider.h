#pragma once

#include "types/prefab/prefab.h"
#include "types/vector2/vector2.h"

namespace Touhou {
	class PlayerCollider : public BigNgine::Prefab {
	public:
		const BigNgine::Vector2 playerColliderSize = BigNgine::Vector2(10.f, 10.f);

		/// @brief Creates a new PlayerCollider prefab.
		/// @param args Arguments to pass to the prefab (no arguments needed).
		/// @return A new PlayerCollider prefab.
		BigNgine::Entity* Create(void** args) override;
	};
}
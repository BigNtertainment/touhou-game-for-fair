#pragma once

#include "types/prefab/prefab.h"
#include "types/vector2/vector2.h"

namespace Touhou {
	class PlayerCollider : public BigNgine::Prefab {
	public:
		const BigNgine::Vector2 playerColliderSize = BigNgine::Vector2(10.f, 10.f);

		BigNgine::Entity* Create(void** args) override;
	};
}
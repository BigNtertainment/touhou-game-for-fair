#pragma once

#include "types/prefab/prefab.h"

namespace Touhou {
	class EnemySmall : public BigNgine::Prefab {
	public:
		BigNgine::Entity* Create(void** args) override;
	};
}
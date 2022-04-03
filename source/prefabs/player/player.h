#pragma once

#include "types/prefab/prefab.h"
#include "types/vector2/vector2.h"
#include <string>

namespace Touhou {
	class Player : public BigNgine::Prefab {
	public:
		const BigNgine::Vector2 playerSize = BigNgine::Vector2(100.f, 100.f);
		const std::string playerTexture = "./assets/img/mariss.png";

		BigNgine::Entity* Create(void** args) override;
	};
}
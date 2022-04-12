#pragma once
#include "types/behaviour/behaviour.h"

namespace Touhou {
	class BulletBehaviour : public BigNgine::Behaviour {
	public:
		BigNgine::Vector2 direction;

		BulletBehaviour(BigNgine::Vector2 direction);

		void Update(int deltaTime) override;
	};
}
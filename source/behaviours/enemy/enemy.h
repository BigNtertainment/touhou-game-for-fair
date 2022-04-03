#pragma once

#include "types/behaviour/behaviour.h"

namespace Touhou {
	class EnemyBehaviour : public BigNgine::Behaviour {
		int health = 1;
	public:
		void Damage();

		void Die();
	};
}
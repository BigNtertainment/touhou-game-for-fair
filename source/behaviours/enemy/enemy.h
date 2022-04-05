#pragma once

#include "types/behaviour/behaviour.h"

namespace Touhou {
	class EnemyBehaviour : public BigNgine::Behaviour {
		int health = 1;

		BigNgine::Entity* model;
	public:
		EnemyBehaviour(BigNgine::Entity* _model);

		void Damage();

		void Die();
	};
}
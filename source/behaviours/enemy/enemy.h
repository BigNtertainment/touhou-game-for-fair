#pragma once

#include "types/behaviour/behaviour.h"
#include "other/score/score.h"

namespace Touhou {
	class EnemyBehaviour : public BigNgine::Behaviour {
		int health = 3;

		BigNgine::Entity* model;
	public:
		EnemyBehaviour(BigNgine::Entity* _model);

		void Damage();

		void Die();
	};
}
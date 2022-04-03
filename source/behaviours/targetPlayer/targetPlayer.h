#pragma once
#include "../../types/behaviour/behaviour.h"
#include "../../types/entity/entity.h"
#include "../bullet/bullet.h"
#include "../../types/vector2/vector2.h"
#include "../../global/logger/logger.h"
#include <math.h>

namespace Touhou
{
	class TargetPlayerBehaviour : public BigNgine::Behaviour
	{
	public:
		TargetPlayerBehaviour(Entity* _player) : player{_player} {};

		void Start();

		void Update(int deltaTime);

		void Destroy();
	
	private:
		Entity* player;
		unsigned short int max_pivot;
		float angle;
	}
};
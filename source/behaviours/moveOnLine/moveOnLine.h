#pragma once
#include "../../types/behaviour/behaviour.h"
#include "../../types/entity/entity.h"
#include "../bullet/bullet.h"
#include "../../types/vector2/vector2.h"
#include "../../global/logger/logger.h"
#include <math.h>
#include <algorithm>

namespace Touhou
{
	class MoveOnLineBehaviour : public BigNgine::Behaviour
	{
	public:
		MoveOnLineBehaviour(double _angle = 0, unsigned int _pixels_per_second = 50) : angle(_angle), pixels_per_second(_pixels_per_second) {};

		void Start();

		void Update(int deltaTime);

		void Destroy();
	
	private:
		Touhou::BulletBehaviour * bullet;
		double angle;
		unsigned int pixels_per_second; 
	};
};
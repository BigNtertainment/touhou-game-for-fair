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
	class TargetPlayerBehaviour : public BigNgine::Behaviour
	{
	public:
		TargetPlayerBehaviour(BigNgine::Entity* _player, double _max_pivot = 1, unsigned int _pixels_per_second = 50) : player(_player), max_pivot(_max_pivot), pixels_per_second(_pixels_per_second) {};

		void Start();

		void Update(int deltaTime);

		void Destroy();
	
	private:
		BigNgine::Entity* player;
		Touhou::BulletBehaviour * bullet;
		BigNgine::Vector2 vector;
		double max_pivot;
		unsigned int pixels_per_second; 
		double angle;
	};
};
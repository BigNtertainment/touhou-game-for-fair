#include "targetPlayer.h"

#include "other/gameStatus/gameStatus.h"

#include <corecrt_math.h>
#include <corecrt_math_defines.h>

void Touhou::TargetPlayerBehaviour::Start()
{
	bullet = parent->GetBehaviour<Touhou::BulletBehaviour>();
	if (bullet == nullptr)
	{
		Logger::Error("BulletBehaviour not found");
		return;
	}
}

void Touhou::TargetPlayerBehaviour::Update(int deltaTime)
{
	if(!GameStatus::running)
		return;

	vector = player->position - parent->position;
    angle = atan(vector.y / vector.x) * 180 / M_PI;
	if(vector.x<0)
		angle += 180;
	 angle = angle - floor(angle/360)*360;
	double a, pa, result;
	pa = parent->rotation - floor(parent->rotation/360)*360 - 90;
    a = pa - angle;
	if(a>180)
		a = -(360-a);
	if(a<-180)
		a = 360+a;
    parent->rotation -= std::clamp(a,-(double)max_pivot,(double)max_pivot);


	bullet->direction.x = cos(pa / 180 * M_PI) * (float)pixels_per_second; // cos(parent->rotation) * 50 - sin(parent->rotation) * 50;


	bullet->direction.y = sin(pa / 180 * M_PI) * (float)pixels_per_second; // sin(parent->rotation) * 50 - cos(parent->rotation) * 50;
}

void Touhou::TargetPlayerBehaviour::Destroy() {};                                                          

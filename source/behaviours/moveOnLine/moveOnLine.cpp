#include "moveOnLine.h"
#include <corecrt_math.h>
#include <corecrt_math_defines.h>

void Touhou::MoveOnLineBehaviour::Start()
{
    bullet = parent->GetBehaviour<Touhou::BulletBehaviour>();
	if (bullet == nullptr)
	{
		Logger::Error("BulletBehaviour not found");
		return;
	}
}

void Touhou::MoveOnLineBehaviour::Update(int deltaTime)
{
    bullet->direction.x = cos(angle / 180 * M_PI) * (float)pixels_per_second; // cos(parent->rotation) * 50 - sin(parent->rotation) * 50;
	bullet->direction.y = sin(angle / 180 * M_PI) * (float)pixels_per_second; // sin(parent->rotation) * 50 - cos(parent->rotation) * 50;
    parent->rotation = angle + 90;
}

void Touhou::MoveOnLineBehaviour::Destroy() {}

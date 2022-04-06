#pragma once

#include "prefabs/playerBullet/playerBullet.h"
#include "prefabs/playerBulletCollider/playerBulletCollider.h"
#include "types/scene/scene.h"
#include "types/entity/entity.h"

namespace Touhou {
	void CreatePlayerBullet(
		BigNgine::Scene* scene,
		BigNgine::Entity* gameArea,
		BigNgine::Vector2 position,
		float bulletDirection = -90.f,
		float bulletSpeed = 600.f
	);
}
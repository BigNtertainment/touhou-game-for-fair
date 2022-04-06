#pragma once

#include "prefabs/playerBullet/playerBullet.h"
#include "prefabs/playerBulletCollider/playerBulletCollider.h"
#include "types/scene/scene.h"
#include "types/entity/entity.h"

namespace Touhou {
	void CreateEnemyBullet(
		BigNgine::Scene* scene,
		BigNgine::Entity* gameArea,
		BigNgine::Vector2 position,
		BigNgine::Vector2 size,
		float bulletDirection = -90.f,
		float bulletSpeed = 600.f
	);
}
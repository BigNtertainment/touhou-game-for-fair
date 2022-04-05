#pragma once

#include "types/scene/scene.h"
#include "types/entity/entity.h"
#include "types/vector2/vector2.h"
#include "behaviours/renderer/renderer.h"
#include "behaviours/enemy/enemy.h"
#include "behaviours/circleCollider/circleCollider.h"

namespace Touhou {
	void CreateEnemy(BigNgine::Scene*, BigNgine::Entity* gameArea, BigNgine::Vector2 position);
}
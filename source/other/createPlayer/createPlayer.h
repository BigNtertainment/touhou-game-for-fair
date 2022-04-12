#pragma once

#include "types/scene/scene.h"
#include "types/entity/entity.h"

namespace Touhou {
	BigNgine::Entity* CreatePlayer(BigNgine::Scene*, BigNgine::Entity* gameArea);
}
#pragma once

#include "types/behaviour/behaviour.h"
#include "types/entity/entity.h"

namespace Touhou {
	class BulletDestructionBehaviour : public BigNgine::Behaviour {
		BigNgine::Entity* boundBox;
	public:
		BulletDestructionBehaviour(BigNgine::Entity* boundBox);

		void Update(int) override;
	};
}
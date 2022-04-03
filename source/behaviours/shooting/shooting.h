#include "types/behaviour/behaviour.h"
#include "types/entity/entity.h"
#include "prefabs/playerBullet/playerBullet.h"

namespace Touhou {
	class ShootingBehaviour : public BigNgine::Behaviour {
		float cooldownTimer = 0.f;
		const float bulletSpeed = 500.f;

		BigNgine::Entity* boundBox;
	public:
		float cooldown = 0.15f;

		ShootingBehaviour(BigNgine::Entity* boundBox);

		void Update(int deltaTime) override;
	};
}
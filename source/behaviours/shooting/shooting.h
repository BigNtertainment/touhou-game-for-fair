#include "types/behaviour/behaviour.h"
#include "types/entity/entity.h"
#include "prefabs/playerBullet/playerBullet.h"

namespace Touhou {
	class ShootingBehaviour : public BigNgine::Behaviour {
		float cooldownTimer = 0.f;
		const float bulletSpeed = 300.f;

		BigNgine::Entity* boundBox;
	public:
		float cooldown = 0.1f;

		ShootingBehaviour(BigNgine::Entity* boundBox);

		void Update(int deltaTime) override;
	};
}
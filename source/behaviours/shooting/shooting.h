#include "types/behaviour/behaviour.h"
#include "prefabs/playerBullet/playerBullet.h"

namespace Touhou {
	class ShootingBehaviour : public BigNgine::Behaviour {
		float cooldownTimer = 0.f;
		const float bulletSpeed = 300.f;
	public:
		float cooldown = 0.1f;

		void Update(int deltaTime) override;
	};
}
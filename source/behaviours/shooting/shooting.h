#include "types/behaviour/behaviour.h"
#include "types/entity/entity.h"
#include "prefabs/playerBullet/playerBullet.h"

namespace Touhou {
	class ShootingBehaviour : public BigNgine::Behaviour {
		// We set the cooldown at the start to 500ms so that the player won't shoot after he pressed 'z' in the menu
		float cooldownTimer = 0.5f;
		const float bulletSpeed = 600.f;
		const float bulletDirection =-90.f;

		BigNgine::Entity* boundBox;
	public:
		float cooldown = 0.15f;

		ShootingBehaviour(BigNgine::Entity* boundBox);

		void Update(int deltaTime) override;
	};
}
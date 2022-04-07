#include "shooting.h"

Touhou::ShootingBehaviour::ShootingBehaviour(BigNgine::Entity* boundBox) :
	boundBox(boundBox) {}

void Touhou::ShootingBehaviour::Update(int deltaTime) {
	if(cooldownTimer > 0.f)
	cooldownTimer -= deltaTime / 1000.f;

	if(Input::Get(BIGNGINE_KEY_Z) && cooldownTimer <= 0.f) {
		auto bulletPrefab = PlayerBullet();

		BigNgine::Vector2 bulletPosition = parent->position + parent->size / 2.f - PlayerBullet::bulletSize / 2.f;

		void* args[] = {
			(void*)&bulletPosition,
			(void*)&bulletDirection,
			(void*)&bulletSpeed,    
			(void*)boundBox
		};

		parent->GetParentScene()->AddPrefabToFront(bulletPrefab, args);

		cooldownTimer = cooldown;
	}
}
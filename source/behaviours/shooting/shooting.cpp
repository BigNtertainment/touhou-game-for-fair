#include "shooting.h"

#include "other/createPlayerBullet/createPlayerBullet.h"
#include "other/gameStatus/gameStatus.h"

Touhou::ShootingBehaviour::ShootingBehaviour(BigNgine::Entity* boundBox) :
	boundBox(boundBox) {}

void Touhou::ShootingBehaviour::Update(int deltaTime) {
	if(!GameStatus::running)
		return;

	if(cooldownTimer > 0.f)
		cooldownTimer -= deltaTime / 1000.f;

	if(Input::Get(BIGNGINE_KEY_Z) && cooldownTimer <= 0.f) {
		CreatePlayerBullet(
			parent->GetParentScene(),
			boundBox,
			parent->position
				+ BigNgine::Vector2(
					parent->size.x / 2.f - PlayerBullet::bulletSize.x / 4.f,
					-PlayerBullet::bulletSize.y
				),
			-90.f,
			600.f
		);

		cooldownTimer = cooldown;
	}
}
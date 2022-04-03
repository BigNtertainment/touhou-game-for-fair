#include "playerCollider.h"

#include "behaviours/circleCollider/circleCollider.h"

BigNgine::Entity* Touhou::PlayerCollider::Create(void** args) {
	auto* gameArea = static_cast<BigNgine::Entity*>(args[0]);

	auto* playerCollider = new BigNgine::Entity(
		BigNgine::Vector2(0.f, 0.f),
		0.f,
		playerColliderSize
	);
	playerCollider->SetDepth(0.f);

	auto* playerColliderBehaviour = new Touhou::CircleColliderBehaviour();

	playerCollider->AddBehaviour(playerColliderBehaviour);

	return playerCollider;
}
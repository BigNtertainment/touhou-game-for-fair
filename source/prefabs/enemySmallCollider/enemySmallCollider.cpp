#include "enemySmallCollider.h"
#include "behaviours/circleCollider/circleCollider.h"
#include "behaviours/enemyMovement/enemyMovement.h"

BigNgine::Entity* Touhou::EnemySmallCollider::Create(void** args) {
    BigNgine::Entity* gameArea = (BigNgine::Entity*)args[0];

    BigNgine::Entity* enemyCollider = new BigNgine::Entity(
        gameArea->position,
        0.f,
        BigNgine::Vector2(enemyColliderSize, enemyColliderSize)
    );

    enemyCollider->AddBehaviour(new CircleColliderBehaviour());
	enemyCollider->AddBehaviour(new EnemyMovementBehaviour(
		gameArea,
		*(EnemyMovementBehaviour::MovementFunction*)args[1]
	));

    return enemyCollider;
}
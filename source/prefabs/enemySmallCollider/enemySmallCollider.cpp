#include "enemySmallCollider.h"
#include "behaviours/circleCollider/circleCollider.h"
#include "behaviours/enemyMovement/enemyMovement.h"
#include "behaviours/enemy/enemy.h"
#include "behaviours/follow/follow.h"
#include "behaviours/bulletDestruction/bulletDestruction.h"
#include "behaviours/renderer/renderer.h"

BigNgine::Entity* Touhou::EnemySmallCollider::Create(void** args) {
    BigNgine::Entity* gameArea = (BigNgine::Entity*)args[0];

    BigNgine::Entity* enemyCollider = new BigNgine::Entity(
        gameArea->position,
        0.f,
        BigNgine::Vector2(enemyColliderSize, enemyColliderSize)
    );

	enemyCollider->SetDepth(0.f);

	enemyCollider->tag = "Enemy";

    enemyCollider->AddBehaviour(new CircleColliderBehaviour());
	enemyCollider->AddBehaviour(new EnemyMovementBehaviour(
		gameArea,
		*(EnemyMovementBehaviour::MovementFunction*)args[1]
	));

	auto* model = (BigNgine::Entity*)args[2];

    enemyCollider->AddBehaviour(new EnemyBehaviour(model));

	BigNgine::TextureRendererBehaviour* debugRenderer = new BigNgine::TextureRendererBehaviour();

	debugRenderer->AddTexture("./assets/img/mariss.png");

	enemyCollider->AddBehaviour(debugRenderer);

	// To destroy the enemy when it leaves the game area
	// We should probably change the name of this behaviour
	model->AddBehaviour(new BulletDestructionBehaviour(gameArea));

	model->AddBehaviour(new BigNgine::FollowBehaviour(
		enemyCollider,
		model->size / -2.f
	));

    return enemyCollider;
}
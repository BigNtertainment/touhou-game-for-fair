#include "enemyBulletCollider.h"

#include "behaviours/circleCollider/circleCollider.h"
#include "behaviours/targetPlayer/targetPlayer.h"
#include "behaviours/follow/follow.h"
#include "behaviours/bulletDestruction/bulletDestruction.h"
#include "other/gameStatus/gameStatus.h"

#include <corecrt_math.h>
#include <corecrt_math_defines.h>

BigNgine::Entity* Touhou::EnemyBulletCollider::Create(void **args) {
	BigNgine::Entity* model = (BigNgine::Entity*)(args[0]);

	float angle = *(float*)args[2];

	BigNgine::Entity* enemyBulletCollider = new BigNgine::Entity(
		model->position + model->size / 2.f,
		angle,
		model->size / 2.f
	);

	enemyBulletCollider->SetDepth(0.f);

	enemyBulletCollider->tag = "EnemyBullet";

	enemyBulletCollider->AddBehaviour(new BulletBehaviour(BigNgine::Vector2(0.f, 0.f)));

	enemyBulletCollider->AddBehaviour(new Touhou::TargetPlayerBehaviour(
		(BigNgine::Entity*)args[1],
		0.35f,
		200.f
	));

	auto* collider = new CircleColliderBehaviour();

	collider->name = "enemyBullet_collider";

	collider->SetCallback([collider, model](CircleColliderBehaviour* other) {
		if(other->GetParent()->tag != "PlayerCollider")
			return;
		
		Logger::Log("player death");

		GameStatus::Lose();

		collider->GetParent()->SetActive(false);
		model->SetActive(false);
		other->GetParent()->SetActive(false);
	});

	enemyBulletCollider->AddBehaviour(collider);

	model->AddBehaviour(new BigNgine::FollowBehaviour(
		enemyBulletCollider,
		model->size / 2.f
	));

	return enemyBulletCollider;
}
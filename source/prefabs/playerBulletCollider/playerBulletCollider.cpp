#include "playerBulletCollider.h"

#include "behaviours/circleCollider/circleCollider.h"
#include "behaviours/moveOnLine/moveOnLine.h"
#include "behaviours/enemy/enemy.h"
#include "behaviours/follow/follow.h"

BigNgine::Entity* Touhou::PlayerBulletCollider::Create(void** args) {
	BigNgine::Entity* model = (BigNgine::Entity*)args[0];

	BigNgine::Entity* playerBulletCollider = new BigNgine::Entity(
		model->position + model->size / 2.f,
		0.f,
		model->size / 2.f
	);

	playerBulletCollider->AddBehaviour(new BulletBehaviour(BigNgine::Vector2(0.0f, 0.0f)));
	playerBulletCollider->AddBehaviour(new MoveOnLineBehaviour(*(float*)args[1], *(float*)args[2]));

	auto* collider = new CircleColliderBehaviour();

	collider->name = "playerBullet_collider";

	collider->SetCallback([playerBulletCollider, model](CircleColliderBehaviour* other) {
		if(other->GetParent()->tag != "Enemy")
			return;

		Touhou::EnemyBehaviour* enemy = other->GetParent()->GetBehaviour<Touhou::EnemyBehaviour>();

		if(enemy == nullptr) {
			Logger::Error("EnemyBehaviour not found on an entity tagged as \"Enemy\".");
		}

		enemy->Damage();

		playerBulletCollider->GetParentScene()->RemoveEntity(model);
		playerBulletCollider->GetParentScene()->RemoveEntity(playerBulletCollider);
	});

	playerBulletCollider->AddBehaviour(collider);

	model->AddBehaviour(new BigNgine::FollowBehaviour(
			playerBulletCollider,
			model->size / -2.f
		)
	);

	return playerBulletCollider;
}
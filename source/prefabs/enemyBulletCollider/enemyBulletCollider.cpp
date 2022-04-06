#include "enemyBulletCollider.h"

#include "behaviours/circleCollider/circleCollider.h"
#include "behaviours/targetPlayer/targetPlayer.h"
#include "behaviours/enemy/enemy.h"

BigNgine::Entity* Touhou::EnemyBulletCollider::Create(void **args) {
	BigNgine::Entity* model = (BigNgine::Entity*)(args[0]);

	BigNgine::Entity* enemyBulletCollider = new BigNgine::Entity(
		model->position + model->size / 4.f,
		0.f,
		model->size / 2.f
	);

	enemyBulletCollider->SetDepth(0.f);

	enemyBulletCollider->tag = "EnemyBullet";

	enemyBulletCollider->AddBehaviour(new BulletBehaviour(BigNgine::Vector2(0.0f, -1.0f)));
	enemyBulletCollider->AddBehaviour(new Touhou::TargetPlayerBehaviour(
		(BigNgine::Entity*)args[2],
		1,
		*(int*)args[3]
	));

	auto* collider = new CircleColliderBehaviour();

	collider->name = "enemyBullet_collider";

	collider->SetCallback([collider](CircleColliderBehaviour* other) {
		if(other->GetParent()->tag != "Player")
			return;


		Logger::Log("player died");
		// Touhou::EnemyBehaviour* enemy = other->GetParent()->GetBehaviour<Touhou::EnemyBehaviour>();

		// if(enemy == nullptr) {
		// 	Logger::Error("EnemyBehaviour not found on an entity tagged as \"Enemy\".");
		// 	return;
		// }

		// enemy->Damage();

		if(collider && collider->GetParent() && collider->GetParent()->GetParentScene())
			collider->GetParent()->GetParentScene()->RemoveEntity(collider->GetParent());
	});

	return enemyBulletCollider;
}
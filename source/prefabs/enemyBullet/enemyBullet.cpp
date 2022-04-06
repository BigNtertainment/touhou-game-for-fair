#include "enemyBullet.h"

#include "behaviours/bullet/bullet.h"
#include "behaviours/renderer/renderer.h"
#include "behaviours/bulletDestruction/bulletDestruction.h"
#include "behaviours/circleCollider/circleCollider.h"
#include "behaviours/targetPlayer/targetPlayer.h"
#include "behaviours/enemy/enemy.h"

#include <cstdlib>
#include <chrono>

const BigNgine::Vector2 Touhou::EnemyBullet::bulletSize = BigNgine::Vector2(20.f, 20.f);

BigNgine::Entity* Touhou::EnemyBullet::Create(void** args) {
	auto* bullet = new BigNgine::Entity(
		*(BigNgine::Vector2*)args[0],
		0.f,
		bulletSize
	);

	bullet->SetDepth(1.f);

	bullet->tag = "EnemyBullet";

	bullet->AddBehaviour(new BulletBehaviour(BigNgine::Vector2(0.0f, -1.0f)));
	bullet->AddBehaviour(new Touhou::TargetPlayerBehaviour(
		(BigNgine::Entity*)args[2],
		1,
		*(int*)args[1]
	));

	BigNgine::TextureRendererBehaviour* renderer = new BigNgine::TextureRendererBehaviour();

	renderer->name = "enemyBullet_renderer";

	renderer->AddTexture(texturePath.c_str());

	bullet->AddBehaviour(renderer);

	auto* bulletDestruction = new BulletDestructionBehaviour((BigNgine::Entity*)args[3]);

	bulletDestruction->name = "enemyBullet_destruction";

	bullet->AddBehaviour(bulletDestruction);

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

	bullet->AddBehaviour(collider);

	return bullet;
}
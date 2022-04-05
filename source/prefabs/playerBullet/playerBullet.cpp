#include "playerBullet.h"

#include "behaviours/bullet/bullet.h"
#include "behaviours/renderer/renderer.h"
#include "behaviours/bulletDestruction/bulletDestruction.h"
#include "behaviours/circleCollider/circleCollider.h"
#include "behaviours/moveOnLine/moveOnLine.h"
#include "behaviours/enemy/enemy.h"

const BigNgine::Vector2 Touhou::PlayerBullet::bulletSize = BigNgine::Vector2(20.f, 20.f);

//TODO: Make the bullet not visible outside of the game area (probably by drawing something over it)
BigNgine::Entity* Touhou::PlayerBullet::Create(void** args) {
	auto* bullet = new BigNgine::Entity(
		*(BigNgine::Vector2*)args[0],
		0.f,
		bulletSize
	);

	bullet->SetDepth(1.f);

	bullet->tag = "PlayerBullet";

	bullet->AddBehaviour(new BulletBehaviour(BigNgine::Vector2(0.0f, 0.0f)));
	bullet->AddBehaviour(new MoveOnLineBehaviour(*(float*)args[1], *(float*)args[2]));

	BigNgine::TextureRendererBehaviour* renderer = new BigNgine::TextureRendererBehaviour();

	renderer->name = "playerBullet_renderer";

	renderer->AddTexture("./assets/img/bullet1.png");

	bullet->AddBehaviour(renderer);

	auto* bulletDestruction = new BulletDestructionBehaviour((BigNgine::Entity*)args[3]);

	bulletDestruction->name = "playerBullet_destruction";

	bullet->AddBehaviour(bulletDestruction);

	auto* collider = new CircleColliderBehaviour();

	collider->name = "playerBullet_collider";

	collider->SetCallback([collider](CircleColliderBehaviour* other) {
		if(other->GetParent()->tag != "Enemy")
			return;

		Touhou::EnemyBehaviour* enemy = other->GetParent()->GetBehaviour<Touhou::EnemyBehaviour>();

		if(enemy == nullptr) {
			Logger::Error("EnemyBehaviour not found on an entity tagged as \"Enemy\".");
			return;
		}

		enemy->Damage();

		BigNgine::Entity* parent = collider->GetParent();

		BigNgine::Scene* scene = parent->GetParentScene();

		scene->RemoveEntity(collider->GetParent());
	});

	bullet->AddBehaviour(collider);

	return bullet;
}
#include "enemyBullet.h"

#include "behaviours/bullet/bullet.h"
#include "behaviours/renderer/renderer.h"
#include "behaviours/bulletDestruction/bulletDestruction.h"

#include <cstdlib>
#include <chrono>

BigNgine::Entity* Touhou::EnemyBullet::Create(void** args) {
	auto* bullet = new BigNgine::Entity(
		*(BigNgine::Vector2*)args[0],
		0.f,
		*(BigNgine::Vector2*)args[1]
	);

	bullet->SetDepth(1.f);

	bullet->tag = "EnemyBulletModel";

	BigNgine::TextureRendererBehaviour* renderer = new BigNgine::TextureRendererBehaviour();

	renderer->name = "enemyBullet_renderer";

	renderer->AddTexture(texturePath.c_str());

	bullet->AddBehaviour(renderer);

	auto* bulletDestruction = new BulletDestructionBehaviour((BigNgine::Entity*)args[3]);

	bulletDestruction->name = "enemyBullet_destruction";

	bullet->AddBehaviour(bulletDestruction);

	return bullet;
}
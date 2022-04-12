#include "playerBullet.h"

#include "behaviours/bullet/bullet.h"
#include "behaviours/renderer/renderer.h"
#include "behaviours/bulletDestruction/bulletDestruction.h"

const BigNgine::Vector2 Touhou::PlayerBullet::bulletSize = BigNgine::Vector2(20.f, 20.f);

//TODO: Make the bullet not visible outside of the game area (probably by drawing something over it)
BigNgine::Entity* Touhou::PlayerBullet::Create(void** args) {
	auto* bullet = new BigNgine::Entity(
		*(BigNgine::Vector2*)args[0],
		0.f,
		bulletSize
	);

	bullet->SetDepth(.1f);

	bullet->tag = "PlayerBulletModel";

	BigNgine::TextureRendererBehaviour* renderer = new BigNgine::TextureRendererBehaviour();

	renderer->name = "playerBullet_renderer";

	renderer->AddTexture("./assets/img/bullet1.png");

	bullet->AddBehaviour(renderer);
	
	auto* bulletDestruction = new BulletDestructionBehaviour(
		(BigNgine::Entity*)args[1]
	);

	bulletDestruction->name = "playerBullet_destruction";

	bullet->AddBehaviour(bulletDestruction);

	return bullet;
}
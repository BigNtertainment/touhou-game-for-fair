#include "playerBullet.h"

#include "behaviours/bullet/bullet.h"
#include "behaviours/renderer/renderer.h"
#include "behaviours/bulletDestruction/bulletDestruction.h"

const BigNgine::Vector2 Touhou::PlayerBullet::bulletSize = BigNgine::Vector2(50.f, 50.f);

// TODO: Destroy bullets when they leave the game area
BigNgine::Entity* Touhou::PlayerBullet::Create(void** args) {
	auto* bullet = new BigNgine::Entity(
		*(BigNgine::Vector2*)args[0],
		0.f,
		bulletSize
	);

	bullet->SetDepth(0.f);

	bullet->AddBehaviour(new BulletBehaviour(*(BigNgine::Vector2*)args[1]));

	BigNgine::TextureRendererBehaviour* renderer = new BigNgine::TextureRendererBehaviour();

	renderer->AddTexture("./assets/img/mariss.png");

	bullet->AddBehaviour(renderer);

	bullet->AddBehaviour(new BulletDestructionBehaviour((BigNgine::Entity*)args[2]));

	return bullet;
}
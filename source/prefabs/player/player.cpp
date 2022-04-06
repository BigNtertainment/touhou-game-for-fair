#include "player.h"

#include "behaviours/renderer/renderer.h"
#include "behaviours/playerMovement/playerMovement.h"
#include "behaviours/shooting/shooting.h"

BigNgine::Entity* Touhou::Player::Create(void** args) {
	BigNgine::Entity* gameArea = (BigNgine::Entity*)args[0];

	auto* player = new BigNgine::Entity(
		BigNgine::Vector2(
			gameArea->position.x + gameArea->size.x / 2.f - playerSize.x,
			gameArea->position.y + gameArea->size.y - playerSize.y - 10.f
		),
		0.f,
		playerSize
	);
// TODO(tymon): wtf???
	player->SetDepth(1.f);

	player->tag = "Player";

	auto* playerRenderer = new BigNgine::TextureRendererBehaviour();

	playerRenderer->AddTexture("./assets/img/mariss.png");

	player->AddBehaviour(playerRenderer);
	player->AddBehaviour(new Touhou::PlayerMovement(gameArea));
	player->AddBehaviour(new Touhou::ShootingBehaviour(gameArea));

	return player;
}
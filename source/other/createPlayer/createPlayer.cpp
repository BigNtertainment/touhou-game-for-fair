#include "createPlayer.h"

#include "prefabs/player/player.h"
#include "prefabs/playerCollider/playerCollider.h"
#include "behaviours/follow/follow.h"

BigNgine::Entity* Touhou::CreatePlayer(BigNgine::Scene* scene, BigNgine::Entity* gameArea) {
	auto playerPrefab = Touhou::Player();

	void* playerArgs[] = {
		gameArea
	};

	auto* player = scene->AddPrefab(playerPrefab, playerArgs);

	auto playerColliderPrefab = Touhou::PlayerCollider();

	auto* playerCollider = scene->AddPrefab(playerColliderPrefab);

	playerCollider->AddBehaviour(new BigNgine::FollowBehaviour(player, player->size / 2.f));

	return playerCollider;
}
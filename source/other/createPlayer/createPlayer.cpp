#include "createPlayer.h"

#include "prefabs/player/player.h"
#include "prefabs/playerCollider/playerCollider.h"
#include "behaviours/follow/follow.h"

void Touhou::CreatePlayer(BigNgine::Scene* scene, BigNgine::Entity* gameArea) {
	auto playerPrefab = Touhou::Player();

	void* playerArgs[] = {
		gameArea
	};

	scene->AddPrefab(playerPrefab, playerArgs, [scene, gameArea](BigNgine::Entity* player) {
		auto playerColliderPrefab = Touhou::PlayerCollider();

		void* playerColliderArgs[] = {
			gameArea
		};

		scene->AddPrefab(playerColliderPrefab, playerColliderArgs, [player](BigNgine::Entity* playerCollider) {
			playerCollider->AddBehaviour(new BigNgine::FollowBehaviour(player, player->size / 2.f - playerCollider->size / 2.f));
		});
	});
}
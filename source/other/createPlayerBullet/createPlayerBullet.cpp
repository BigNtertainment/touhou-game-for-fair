#include "createPlayerBullet.h"

#include "prefabs/playerBullet/playerBullet.h"
#include "prefabs/playerBulletCollider/playerBulletCollider.h"

void Touhou::CreatePlayerBullet(
	BigNgine::Scene *scene,
	BigNgine::Entity *gameArea,
	BigNgine::Vector2 position,
	float bulletDirection,
	float bulletSpeed
) {
	auto playerBulletPrefab = PlayerBullet();

	void* args[] = {
		(void*)&position,
		gameArea
	};

	scene->AddPrefabToFront(
		playerBulletPrefab,
		args, 
		[scene, bulletDirection, bulletSpeed] (BigNgine::Entity* model) {
			auto playerBulletColliderPrefab = PlayerBulletCollider();

			void* args[] = {
				model,
				(void*)&bulletDirection,
				(void*)&bulletSpeed
			};

			scene->AddPrefabToFront(playerBulletColliderPrefab, args);
		}
	);
}
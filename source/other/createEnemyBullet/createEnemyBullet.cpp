#include "createEnemyBullet.h"

#include "prefabs/enemyBullet/enemyBullet.h"
#include "prefabs/enemyBulletCollider/enemyBulletCollider.h"

void Touhou::CreateEnemyBullet(
	BigNgine::Scene *scene,
	BigNgine::Entity *gameArea,
	BigNgine::Vector2 position,
	BigNgine::Vector2 size,
	float bulletDirection,
	float bulletSpeed
) {
	auto enemyBulletPrefab = EnemyBullet();

	void* args[] = {
		(void*)&position,
		(void*)&size,
		gameArea
	};

	scene->AddPrefab(
		enemyBulletPrefab,
		args,
		[scene, bulletDirection, bulletSpeed] (BigNgine::Entity* model) {
			auto enemyBulletColliderPrefab = EnemyBulletCollider();

			void* args[] = {
				model,
				(void*)&bulletDirection,
				(void*)&bulletSpeed
			};

			scene->AddPrefab(enemyBulletColliderPrefab, args);
		}
	);
}
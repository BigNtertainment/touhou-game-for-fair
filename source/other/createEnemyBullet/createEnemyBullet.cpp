#include "createEnemyBullet.h"

#include "prefabs/enemyBullet/enemyBullet.h"
#include "prefabs/enemyBulletCollider/enemyBulletCollider.h"

void Touhou::CreateEnemyBullet(
	BigNgine::Scene *scene,
	BigNgine::Entity *gameArea,
	BigNgine::Entity *player,
	BigNgine::Vector2 position,
	BigNgine::Vector2 size,
	float bulletDirection
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
		[scene, bulletDirection, player] (BigNgine::Entity* model) {
			auto enemyBulletColliderPrefab = EnemyBulletCollider();

			void* args[] = {
				model,
				player,
				(void*)&bulletDirection
			};

			scene->AddPrefab(enemyBulletColliderPrefab, args);
		}
	);
}
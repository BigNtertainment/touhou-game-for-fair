#include "createEnemy.h"

#include "prefabs/enemySmall/enemySmall.h"
#include "prefabs/enemySmallCollider/enemySmallCollider.h"
#include "behaviours/follow/follow.h"

void Touhou::CreateSmallEnemy(
	BigNgine::Scene *scene,
	BigNgine::Entity *gameArea,
	Touhou::EnemyMovementBehaviour::MovementFunction movementFunction
) {
	void* args[] = {
		gameArea,
		(void*)&movementFunction
	};

	auto colliderPrefab = EnemySmallCollider();

	scene->AddPrefab(
		colliderPrefab, args, [gameArea, scene] (BigNgine::Entity* collider) {
			void* args[] = {
				gameArea
			};

			auto enemyPrefab = EnemySmall();

			scene->AddPrefab(
				enemyPrefab, args, [collider] (BigNgine::Entity* entity) {
					entity->AddBehaviour(
						new BigNgine::FollowBehaviour(
							collider,
							entity->size / -2.f + collider->size / 2.f
						)
					);
				}
			);
		}
	);
}

Touhou::EnemyMovementBehaviour::MovementFunction Touhou::ComeAndGo(
	BigNgine::Entity* gameArea,
	BigNgine::Vector2 target,
	float speed,
	float waitTime
) {
	// target = target * gameArea->size;

	const float timeToTarget = target.y / speed;
	const float timeToLeave = target.x / speed;

	return [target, speed, waitTime, timeToTarget, timeToLeave] (int time) -> BigNgine::Vector2 {
		float timeInSeconds = time / 1000.f;

		if(timeInSeconds < timeToTarget) {
			return BigNgine::Vector2(
				target.x,
				timeInSeconds * speed
			);
		}
		
		if(timeInSeconds < timeToTarget + waitTime) {
			return target;
		}

		return BigNgine::Vector2(
			target.x +
				(timeInSeconds - timeToTarget - waitTime) * speed *
				(target.x > 0.5f ? 1.f : -1.f),
			target.y
		);
	};
}
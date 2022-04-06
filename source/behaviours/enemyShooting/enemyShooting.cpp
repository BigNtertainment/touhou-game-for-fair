#include "enemyShooting.h"
#include <stdint.h>

Touhou::EnemyShootingBehaviour::EnemyShootingBehaviour(
	std::vector<uint16_t> intervals,
	BigNgine::Prefab* bulletPrefab
) : bulletPrefab(bulletPrefab), intervals(intervals), timer(0), intervalIndex(0) {}

void Touhou::EnemyShootingBehaviour::Update(int deltaTime) {
	timer += deltaTime;

	if(intervalIndex < intervals.size()) {
		if(timer >= intervals[intervalIndex]) {
			Shoot();

			timer = 0;
			intervalIndex++;
		}

		return;
	}

	// Delete the behaviour when the enemy won't shoot anymore
	delete this;
}

void Touhou::EnemyShootingBehaviour::Shoot() {
	void* args[] = {
		&parent->position
	};

	parent->GetParentScene()->AddPrefab(*bulletPrefab, args);
}

void Touhou::EnemyShootingBehaviour::Destroy() {
	delete bulletPrefab;
}
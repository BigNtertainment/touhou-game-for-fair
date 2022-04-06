#include "types/behaviour/behaviour.h"

#include "types/prefab/prefab.h"

#include <stdint.h>
#include <vector>

namespace Touhou {
	class EnemyShootingBehaviour : BigNgine::Behaviour {
		BigNgine::Prefab* bulletPrefab;
		std::vector<uint16_t> intervals;
		uint32_t timer;
		uint16_t intervalIndex;
	public:
		EnemyShootingBehaviour(std::vector<uint16_t> intervals, BigNgine::Prefab* bulletPrefab);

		void Update(int deltaTime) override;
		void Destroy() override;

		void Shoot();
	};
}
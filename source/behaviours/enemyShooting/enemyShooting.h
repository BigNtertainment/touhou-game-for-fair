#include "types/behaviour/behaviour.h"
#include "types/entity/entity.h"
#include "types/prefab/prefab.h"

#include <stdint.h>
#include <vector>

namespace Touhou {
	class EnemyShootingBehaviour : public BigNgine::Behaviour {
		BigNgine::Entity* gameArea;
		BigNgine::Entity* player;
		std::vector<uint16_t> shotIntervals;
		uint32_t timer = 0;
		uint16_t intervalIndex = 0;
	public:
		static const BigNgine::Vector2 bulletSize;

		EnemyShootingBehaviour(BigNgine::Entity* gameArea, BigNgine::Entity* player, std::vector<uint16_t> shotIntervals);

		void Update(int deltaTime) override;

		void Shoot();
	};
}
#include "types/scene/scene.h"

#include <functional>
#include <vector>

namespace Touhou {
	class EnemyWave {
		static std::vector<EnemyWave*> waves;
		static float timer;
		static uint32_t waveIndex;

	public:
		using SpawnFunction = std::function<void(BigNgine::Scene*)>;

		EnemyWave(BigNgine::Scene* scene, SpawnFunction spawnFunction, float delay);
		~EnemyWave();

		static void Start();
		static void Update(int deltaTime);
	private:
		BigNgine::Scene* scene;
		SpawnFunction spawnFunction;
		float delay;
	};
}
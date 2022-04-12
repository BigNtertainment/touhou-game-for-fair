#include "enemyWave.h"

#include <algorithm>

std::vector<Touhou::EnemyWave*> Touhou::EnemyWave::waves = {};
float Touhou::EnemyWave::timer = 0.f;
uint32_t Touhou::EnemyWave::waveIndex = 0;

Touhou::EnemyWave::EnemyWave(BigNgine::Scene* scene, SpawnFunction spawnFunction, float delay) :
	scene(scene),
	spawnFunction(spawnFunction),
	delay(delay)
{
	waves.push_back(this);
}

Touhou::EnemyWave::~EnemyWave() {
	waves.erase(std::remove(waves.begin(), waves.end(), this), waves.end());
}

void Touhou::EnemyWave::Start() {
	timer = 0.f;
	waveIndex = 0;
}

void Touhou::EnemyWave::Update(int deltaTime) {
	timer += deltaTime / 1000.f;

	if(waveIndex >= waves.size())
		waveIndex = 0;

	if(timer >= waves[waveIndex]->delay) {
		waves[waveIndex]->spawnFunction(waves[waveIndex]->scene);
		waveIndex++;
		timer = 0.f;
	}
}
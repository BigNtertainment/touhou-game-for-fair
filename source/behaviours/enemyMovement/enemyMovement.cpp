#include "enemyMovement.h"

#include "other/gameStatus/gameStatus.h"

Touhou::EnemyMovementBehaviour::EnemyMovementBehaviour(
    BigNgine::Entity* _gameArea,
    Touhou::EnemyMovementBehaviour::MovementFunction _movementFunction
) : movementFunction(_movementFunction), gameArea(_gameArea), timer(0) {}

void Touhou::EnemyMovementBehaviour::Update(int deltaTime) {
	if(!GameStatus::running)
		return;

    timer += deltaTime;
    parent->position =
        gameArea->position + movementFunction(timer) * gameArea->size;
}
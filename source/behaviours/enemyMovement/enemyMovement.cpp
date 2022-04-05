#include "enemyMovement.h"

Touhou::EnemyMovementBehaviour::EnemyMovementBehaviour(
    BigNgine::Entity* _gameArea,
    Touhou::EnemyMovementBehaviour::MovementFunction _movementFunction
) : gameArea(_gameArea), movementFunction(_movementFunction), timer(0) {}

void Touhou::EnemyMovementBehaviour::Update(int deltaTime) {
    timer += deltaTime;
    parent->position =
        gameArea->position + movementFunction(timer) * gameArea->size;
}
#pragma once

#include "types/behaviour/behaviour.h"
#include <functional>

namespace Touhou {
    class EnemyMovementBehaviour : public BigNgine::Behaviour {
    public:
        using MovementFunction = std::function<BigNgine::Vector2(int)>;

        EnemyMovementBehaviour(BigNgine::Entity* _gameArea, MovementFunction _movementFunction);

        void Update(int deltaTime) override;
    private:
        MovementFunction movementFunction;
        BigNgine::Entity* gameArea;
        int timer;
    };
}
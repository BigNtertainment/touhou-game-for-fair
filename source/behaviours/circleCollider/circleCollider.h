#pragma once
#include "../../types/behaviour/behaviour.h"
#include "../../types/vector2/vector2.h"
#include "../../global/logger/logger.h"
#include <math.h>
#include <vector>
#include <functional>
#include <algorithm>

namespace Touhou {
	class CircleColliderBehaviour : public BigNgine::Behaviour {
		using ColliderCallback = std::function<void(CircleColliderBehaviour*)>;
		static std::vector<CircleColliderBehaviour*> colliders;
	public:
		void Start();

		void Update(int deltaTime);

		void Destroy();

		bool IsColliding(CircleColliderBehaviour* collider) const;

		void SetCallback(ColliderCallback _callback);

		~CircleColliderBehaviour();

	private:
		ColliderCallback callback = [](CircleColliderBehaviour*) {};
	};
};

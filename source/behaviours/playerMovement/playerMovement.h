#include "types/behaviour/behaviour.h"

namespace Touhou {
	class PlayerMovement : public BigNgine::Behaviour {
		BigNgine::Entity* boundBox;
	public:
		float speed = 400.f;
		float precisionModeSpeed = speed / 2.f;

		PlayerMovement(BigNgine::Entity* boundBox);

		void Update(int deltaTime) override;
	};
}
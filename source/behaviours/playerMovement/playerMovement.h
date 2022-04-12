#include "types/behaviour/behaviour.h"
#include "types/texture/texture.h"
#include "behaviours/renderer/renderer.h"
#include <vector>

namespace Touhou {
	class PlayerMovement : public BigNgine::Behaviour {
		BigNgine::Entity* boundBox;
	public:
		float speed = 400.f;
		float precisionModeSpeed = speed / 2.f;

		PlayerMovement(BigNgine::Entity* boundBox);
		void Start() override;
		void Update(int deltaTime) override;
	private:
		BigNgine::TextureRendererBehaviour* renderer;
		std::vector<BigNgine::Texture*> textures = std::vector<BigNgine::Texture*>();
	};
}
#include "types/prefab/prefab.h"

namespace Touhou {
	class EnemyBulletCollider : public BigNgine::Prefab {
	public:
		/// @brief Creates a new small enemy collider.
		/// @param void** args Arguments:
		/// - model (BigNgine::Entity*)
		/// - player (BigNgine::Entity*)
		/// - movement angle (float)
		BigNgine::Entity* Create(void** args) override;
	};
}
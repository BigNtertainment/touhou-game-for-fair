#include "types/entity/entity.h"

namespace Touhou {
	class GameStatus {
		GameStatus();
	public:
		static bool running;
		static BigNgine::Entity* loseMenu;
		static BigNgine::Scene* mainMenu;

		static void Lose();
	};
}
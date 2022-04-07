#include "gameStatus.h"

#include "global/input/input.h"

bool Touhou::GameStatus::running = true;
BigNgine::Entity* Touhou::GameStatus::loseMenu = nullptr;
BigNgine::Scene* Touhou::GameStatus::mainMenu = nullptr;

void Touhou::GameStatus::Lose() {
	running = false;

	if(loseMenu == nullptr) {
		Logger::Error("GameStatus::loseMenu is nullptr.");
		return;
	}

	if(mainMenu == nullptr) {
		Logger::Error("GameStatus::mainMenu is nullptr.");
		return;
	}

	loseMenu->SetActive(true);

	Logger::Log(1);

	BigNgine::Scene* scene = loseMenu->GetParentScene();
	
	BigNgine::Scene* menu = mainMenu;

	Logger::Log(2);

	Input::Callback* callback = new Input::Callback([menu](int key, int, int) {
		if(key != BIGNGINE_KEY_Z)
			return;
		
		Logger::Log("a");

		BigNgine::Game::GetInstance()->SetActiveScene(menu);
		Logger::Log("b");
	});
	Logger::Log(3);

	scene->AddCallback(callback);
	Logger::Log(4);
}
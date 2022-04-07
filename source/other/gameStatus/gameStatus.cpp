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

	BigNgine::Scene* scene = loseMenu->GetParentScene();
	
	BigNgine::Scene* menu = mainMenu;

	Input::Callback* callback = new Input::Callback([menu](int key, int, int) {
		if(key != BIGNGINE_KEY_Z)
			return;

		BigNgine::Game::GetInstance()->SetActiveScene(menu);
	});

	scene->AddCallback(callback);
}
#include "behaviour.h"

BigNgine::Behaviour::Behaviour() = default;

BigNgine::Behaviour::~Behaviour() {
	Logger::Log("destroying behaviour " + name);

	Destroy();

	Logger::Log("behaviour destroyed " + name);

	parent->behaviours.erase(std::remove(parent->behaviours.begin(), parent->behaviours.end(), this), parent->behaviours.end());
}

void BigNgine::Behaviour::Start() {}
void BigNgine::Behaviour::Update(int deltaTime) {}
void BigNgine::Behaviour::Destroy() {}
void BigNgine::Behaviour::OnEnable() {}
void BigNgine::Behaviour::OnDisable() {}

void BigNgine::Behaviour::Enable() {
	active = true;
	OnEnable();
}

void BigNgine::Behaviour::Disable() {
	active = false;
	OnDisable();
}

void BigNgine::Behaviour::SetActive(bool _active) {
	if (_active) {
		Enable();
	} else {
		Disable();
	}
}

BigNgine::Entity* BigNgine::Behaviour::GetParent() {
	return parent;
}
#include "entity.h"

BigNgine::Entity::Entity(const BigNgine::Vector2& _position, float _rotation, const BigNgine::Vector2& _size) : position(_position), rotation(_rotation), size(_size) {}


void BigNgine::Entity::SetDepth(float _depth)
{
	depth = _depth;
}

void BigNgine::Entity::AddBehaviour(BigNgine::Behaviour* behaviour) {
	behaviour->parent = this;

	behaviours.push_back(behaviour);
}

void BigNgine::Entity::Start() {
	for(auto & behaviour : behaviours) {
		if(behaviour->active) {
			behaviour->Start();
		}
	}
}

void BigNgine::Entity::Update(int deltaTime) {
	if(!active)
		return;

	uint32_t size = behaviours.size();

	for(int i = 0; i < size; i++) {
		if(behaviours[i]->active) {
			if(behaviours[i] == nullptr) {
				Logger::Error("Behaviour is nullptr");
				continue;
			}

			behaviours[i]->Update(deltaTime);

			if(this == nullptr)
				break;
		}

		size = behaviours.size();
	}
}

BigNgine::Scene* BigNgine::Entity::GetParentScene() {
	return parentScene;
}

void BigNgine::Entity::SetActive(bool _active) {
	active = _active;
}

bool BigNgine::Entity::IsActive() {
	return active;
}

BigNgine::Entity::~Entity() {
	// We do it like that because the behaviour gets deleted from the vector automatically, making the next element index zero
	for(int i = 0; i < behaviours.size(); i++) {
		delete behaviours[0];
	}
}

void BigNgine::Entity::operator delete(void* ptr) {
	free(ptr);
}

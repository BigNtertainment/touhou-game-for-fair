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

	for(auto & behaviour : behaviours) {
		if(behaviour->active) {
			behaviour->Update(deltaTime);

			if(this == nullptr)
				break;
		}
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
	Logger::Log("Entity destroyed " + tag);

	// We do it like that because the behaviour gets deleted from the vector automatically, making the next element index zero
	for(int i = 0; i < behaviours.size(); i++) {
		Logger::Log("Deleting behaviour " + behaviours[0]->name);

		delete behaviours[0];
	}
}

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

BigNgine::Entity::~Entity() {
	for(auto & behaviour : behaviours) {
		delete behaviour;
	}
}

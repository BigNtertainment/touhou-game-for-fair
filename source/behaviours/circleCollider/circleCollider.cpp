#include "circleCollider.h"

auto Touhou::CircleColliderBehaviour::colliders = std::vector<CircleColliderBehaviour*>();

void Touhou::CircleColliderBehaviour::Start()
{
	// Check if collider already exists
	auto it = std::find_if(colliders.begin(), colliders.end(), [this](CircleColliderBehaviour* collider) {
		return collider->GetParent() == parent;
	});

	// If collider already exists, remove it
	if (it != colliders.end())
		colliders.erase(it);

	colliders.push_back(this);
}

void Touhou::CircleColliderBehaviour::Update(int deltaTime)
{
	uint32_t size = colliders.size();

	Logger::Log(1);

	for(uint32_t i = 0; i < size; i++)
	{
		CircleColliderBehaviour* collider = colliders[i];

		if(collider == this)
		{
			continue;
		}

		if(collider == nullptr) {
			Logger::Error("Collider is nullptr");
			colliders.erase(std::remove(colliders.begin(), colliders.end(), collider), colliders.end());
			i--;
			continue;
		}

		if(collider->active && this->IsColliding(collider))
		{
			if(
				collider == nullptr ||
				collider->parent == nullptr ||
				this->parent == nullptr
			) {
				Logger::Error("shit nullptr");
				continue;
			}

			if(callback != nullptr)
				callback(collider);

			continue;
		}

		if(collider == nullptr)
		{
			i--;
			colliders.erase(std::remove(colliders.begin(), colliders.end(), collider), colliders.end());
		}

		size = colliders.size();
	}

	Logger::Log(2);
}

void Touhou::CircleColliderBehaviour::Destroy()
{
	active = false;

	colliders.erase(std::remove(colliders.begin(), colliders.end(), this), colliders.end());

	parent->RemoveBehaviour(this);
}

bool Touhou::CircleColliderBehaviour::IsColliding(Touhou::CircleColliderBehaviour* collider) const
{
	Logger::Log("a");

	if(!active || !collider->active)
		return false;

	// getting distance between center of this collider and passed one
	// im not getting square root of it because its slow
	if(collider->parent == nullptr) {
		Logger::Error("collider has nullptr parent");
		colliders.erase(std::remove(colliders.begin(), colliders.end(), collider), colliders.end());
		return false;
	}

	if(this->parent == nullptr) {
		Logger::Error("what");
		return false;
	}

	Logger::Log("b");
	Logger::Log(parent->position);
	Logger::Log(collider->parent->position);

	double distance_between_circles_squared = 
		pow((this->parent->position.x - collider->parent->position.x), 2)
		+ pow((this->parent->position.y - collider->parent->position.y), 2);
	Logger::Log("c");

	// checking if distance between centers squared is less then sum of radii squared
	return distance_between_circles_squared < pow((this->parent->size.x + collider->parent->size.x), 2);
}

void Touhou::CircleColliderBehaviour::SetCallback(ColliderCallback _callback)
{
	callback = _callback;
}

Touhou::CircleColliderBehaviour::~CircleColliderBehaviour()
{
	Destroy();
}
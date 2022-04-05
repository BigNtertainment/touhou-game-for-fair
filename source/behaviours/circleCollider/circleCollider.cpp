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
	bool encounteredThis = false;

	uint32_t size = colliders.size();

	for(uint32_t i = 0; i < size; i++)
	{
		CircleColliderBehaviour* collider = colliders[i];

		if(collider == this)
		{
			encounteredThis = true;
			continue;
		}

		if(collider == nullptr) {
			Logger::Error("Collider is nullptr");
			continue;
		}

		if(!encounteredThis)
			continue;

		if(collider->active && this->IsColliding(collider))
		{
			collider->callback(this);
			this->callback(collider);
		}

		if(this == nullptr)
			break;

		if(collider == nullptr)
		{
			i--;
		}

		size = colliders.size();
	}
}

void Touhou::CircleColliderBehaviour::Destroy()
{
	colliders.erase(std::remove(colliders.begin(), colliders.end(), this), colliders.end());
}

bool Touhou::CircleColliderBehaviour::IsColliding(Touhou::CircleColliderBehaviour* collider) const
{
// 	getting distance between center of this collider and passed one
// 	im not getting square root of it because its slow
	double distance_between_circles_squared = 
		pow((this->parent->position.x - collider->parent->position.x), 2)
		+ pow((this->parent->position.y - collider->parent->position.y), 2);
// 	checking if distance between centers squared is less then sum of radii squared
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
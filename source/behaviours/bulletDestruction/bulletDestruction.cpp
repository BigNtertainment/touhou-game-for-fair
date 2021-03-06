#include "bulletDestruction.h"
#include "behaviours/follow/follow.h"
#include <vector>

Touhou::BulletDestructionBehaviour::BulletDestructionBehaviour(BigNgine::Entity* boundBox) :
	boundBox(boundBox) {}

void Touhou::BulletDestructionBehaviour::Update(int) {
	if(
		parent->position.x + parent->size.x < boundBox->position.x ||
		parent->position.x > boundBox->position.x + boundBox->size.x ||
		parent->position.y + parent->size.y < boundBox->position.y ||
		parent->position.y > boundBox->position.y + boundBox->size.y
	) {
		std::vector<BigNgine::FollowBehaviour*> followBehaviours =
			parent->GetBehaviours<BigNgine::FollowBehaviour>();

		for(auto* followBehaviour : followBehaviours) {
			delete followBehaviour->followed;
		}

		delete parent;
	}
}
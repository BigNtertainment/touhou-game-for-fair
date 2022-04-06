#include "playerMovement.h"

BigNgine::Vector2 Normalize(BigNgine::Vector2 vector)
{
	float length = sqrt(vector.x * vector.x + vector.y * vector.y);

	if(length == 0.f)
		return vector;

	return {vector.x / length, vector.y / length};
}

Touhou::PlayerMovement::PlayerMovement(BigNgine::Entity* boundBox)
{
	this->boundBox = boundBox;
}

void Touhou::PlayerMovement::Start()
{
	renderer = parent->GetBehaviour<BigNgine::TextureRendererBehaviour>();
	if (renderer == nullptr) {
		Logger::Error("PlayerMovement::Start: TextureRendererBehaviour is nullptr");
	}
	textures.push_back(new BigNgine::Texture("assets/img/Chimata_left.png"));
	textures.push_back(new BigNgine::Texture("assets/img/Chimata_front.png"));
	textures.push_back(new BigNgine::Texture("assets/img/Chimata_right.png"));
}

void Touhou::PlayerMovement::Update(int deltaTime) {
	BigNgine::Vector2 movementVector = BigNgine::Vector2(
		Input::Get(BIGNGINE_KEY_RIGHT) - Input::Get(BIGNGINE_KEY_LEFT),
		Input::Get(BIGNGINE_KEY_DOWN) - Input::Get(BIGNGINE_KEY_UP)
	);
	
	renderer->SetTexture(textures[movementVector.x + 1]);

	bool precisionMode = Input::Get(BIGNGINE_KEY_LEFT_SHIFT);

	if(movementVector.x != 0.f || movementVector.y != 0.f) {
		movementVector = Normalize(movementVector);
	}

	movementVector = movementVector * (precisionMode ? precisionModeSpeed : speed) * deltaTime / 1000.f;

	BigNgine::Vector2 destination = parent->position + movementVector;

	if(destination.x < boundBox->position.x)
		destination.x = boundBox->position.x;
	else if(destination.x + parent->size.x > boundBox->position.x + boundBox->size.x)
		destination.x = boundBox->position.x + boundBox->size.x - parent->size.x;

	if(destination.y < boundBox->position.y)
		destination.y = boundBox->position.y;
	else if(destination.y + parent->size.y > boundBox->position.y + boundBox->size.y)
		destination.y = boundBox->position.y + boundBox->size.y - parent->size.y;

	parent->position = destination;
}
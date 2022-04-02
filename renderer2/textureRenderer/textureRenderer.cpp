#include "textureRenderer.h"

void BigNgine::TextureRendererBehaviour::Start() {
	// Setting up all the relations between points in one entity-square
	float vertices[] = {
	//	positions			texture coords
		1.0f, 0.0f, 0.0f,	1.0f, 0.0f,	// top right
		1.0f, 1.0f, 0.0f,	1.0f, 1.0f,	// bottom right
		0.0f, 1.0f, 0.0f,	0.0f, 1.0f,	// bottom left
		0.0f, 0.0f, 0.0f,	0.0f, 0.0f 	// top left
	};
	
	// How the points form triangles
	unsigned int indicesSquare[] = {
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};
}
#pragma once
#include "external/GLAD/glad.h"
#include "external/GLFW/include/GLFW/glfw3.h"
#include "external/STBI/stb_image.h"
#include "game.h"
#include "logger.h"
#include "fileSystem.h"
#include <string>
#include <iostream>


namespace BigNgine{
	class Texture{
	public:
		Texture(const char* path);
		~Texture();

		void Bind(unsigned int slot = 0);
		void Unbind();

		[[nodiscard]] unsigned int getID() const;
		[[nodiscard]] int getWidth() const;
		[[nodiscard]] int getHeight() const;

	private:
		unsigned int _id;
		int _width, _height;
	};

};

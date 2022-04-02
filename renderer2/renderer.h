#pragma once

#include "glad.h"
#include "GLFW/glfw3.h"
#include "stb_image.h"
#include "../../types/behaviour/behaviour.h"
#include "../../global/game/game.h"
#include "../../global/logger/logger.h"
#include "../../types/texture/texture.h"
#include "../../types/vector2/vector2.h"
#include "../../types/vector3/vector3.h"
#include "../../global/fileSystem/fileSystem.h"
#include <string>
#include <iostream>
#include <map>
#include <vector>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace BigNgine {
	class RendererBehaviour : public Behaviour {
	public:
		/**
		 * @brief Specify the vertex shader to use
		 * 
		 * @param _vertexShader The source code of the vertex shader
		 */
		void SetVertexShader(std::string& _vertexShader);
		/**
		 * @brief Specify the fragment shader to use
		 * 
		 * @param _vertexShader The source code of the fragment shader
		 */
		void SetFragmentShader(std::string& _vertexShader);

		/**
		 * @brief Specify the vertex shader to use
		 * 
		 * @param _vertexShaderPath The path to the vertex shader source
		 */
		void LoadVertexShader(std::string& _vertexShaderPath);
		/**
		 * @brief Specify the fragment shader to use
		 * 
		 * @param _vertexShaderPath The path to the fragment shader source
		 */
		void LoadFragmentShader(std::string& fragmentShaderPath);

		void CompileShaders();
		void BindBuffers();

		void Destroy() override;

	protected:
		unsigned int VBO, VAO, EBO, program = 0, vertexShader = 0, fragmentShader = 0;
	};
}
#include "renderer.h"

void BigNgine::RendererBehaviour::SetVertexShader(std::string& _vertexShader) {
	// Delete the old shader
	if(vertexShader != 0)
		glDeleteShader(vertexShader);

	// Create the shader
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// Compile the shader
	const char *vertexShaderSource = _vertexShader.c_str();

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// Check for errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "Vertex shader compilation failed! Info log: " << infoLog << std::endl;
		vertexShader = 0;
		return;
	}
}

void BigNgine::RendererBehaviour::SetFragmentShader(std::string& _fragmentShader) {
	// Delete the old shader
	if(fragmentShader != 0)
		glDeleteShader(fragmentShader);

	// Create the shader
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Compile the shader
	const char *fragmentShaderSource = _fragmentShader.c_str();

	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// Check for errors
	int success;
	char infoLog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "Fragment shader compilation failed! Info log: " << infoLog << std::endl;
		fragmentShader = 0;
		return;
	}
}

void BigNgine::RendererBehaviour::LoadVertexShader(std::string& _vertexShader) {
	// Read the file contents into a string
	std::string vertexShaderSource = FileSystem::LoadFile(_vertexShader);

	// Set the shader source
	SetVertexShader(vertexShaderSource);
}

void BigNgine::RendererBehaviour::LoadFragmentShader(std::string& _fragmentShader) {
	// Read the file contents into a string
	std::string fragmentShaderSource = FileSystem::LoadFile(_fragmentShader);

	// Set the shader source
	SetFragmentShader(fragmentShaderSource);
}

void BigNgine::RendererBehaviour::CompileShaders() {
	// Delete the old program
	if(program != 0)
		glDeleteProgram(program);

	// Create the program
	program = glCreateProgram();

	// Attach the shaders
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	// Link the program
	glLinkProgram(program);

	// Check for errors
	int success;
	char infoLog[512];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "Shader program linking failed! Info log: " << infoLog << std::endl;
		program = 0;
		return;
	}
}

void BigNgine::RendererBehaviour::BindBuffers() {
	// Binding all the arrays
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	
	glBindVertexArray(VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_square), indices_square, GL_STATIC_DRAW);
	
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)nullptr);
	glEnableVertexAttribArray(0);
//	texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glBindVertexArray(0);
}

void BigNgine::RendererBehaviour::Destroy() {
	// Delete the shaders
	if(vertexShader != 0)
		glDeleteShader(vertexShader);

	if(fragmentShader != 0)
		glDeleteShader(fragmentShader);

	// Delete the program
	if(program != 0)
		glDeleteProgram(program);

	// Delete the buffers
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}
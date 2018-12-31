#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "fileStream/FileStream.h"

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1280, 720, "TicTacToeMinimax", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/* set viewport */
	glViewport(0, 0, 1280, 720);

	/* Initialize GLEW */
	if (glewInit() != GLEW_OK)
		std::cout << "error while initializing glew" << std::endl;

	float vertices[] = {
		-0.75f, 0.5f, 0.0f, 0.75f, 0.5f, 0.0f, 
		-0.75f, 0.0f, 0.0f, 0.75f, 0.0f, 0.0f, 
		-0.75f, -0.5f, 0.0f, 0.75f, -0.5f, 0.0f,
		-0.75f, -1.0f, 0.0f, 0.75f, -1.0f, 0.0f,

		-0.75f, 0.5f, 0.0f, -0.75f, -0.5f, 0.0f,
		-0.25f, 0.5f, 0.0f, -0.25f, -0.5f, 0.0f,
		0.25f, 0.5f, 0.0f, 0.25f, -0.5f, 0.0f,
		0.75f, 0.5f, 0.0f, 0.75f, 0.5f, 0.0f
	};

	/* Vertex Buffer Object */
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	/* Vertex Shader */
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	std::string sourceString = FileStream::ReadFileIntoString("res/shaders/VertexShader.shader");
	const char* vertexShaderSource = sourceString.c_str();
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

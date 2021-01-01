#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void Process_Input(GLFWwindow* window);

int scr_width = 1200, scr_height = 800;

// Used for WASD movement
// Moves triangles
float x_offset_value = 0.0f;
float y_offset_value = 0.0f;

int main()
{
	// Initalize glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create Window
	GLFWwindow* window = glfwCreateWindow(scr_width, scr_height, "Learn OpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initalize GLAD" << std::endl;
		return -1;
	}

	vector<float> square = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
	};

	vector<unsigned int> vertices = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	// Create Shader object
	Shader shader;
	shader.Create("vShader.vs", "fShader.fs");
	shader.Config(square, vertices);
	shader.Load_Texture("car.png", "test.png");
	shader.Unbind();

	// Set texture sampler uniforms
	shader.Use(); // Use shader before setting uniforms
	shader.setInt("texture1", 0);
	shader.setInt("texture2", 1);

	// Render Loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.8f, 0.4f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		Process_Input(window);

		// --- Start Drawing ---
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, shader.texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, shader.texture2);

		shader.Use();
		glBindVertexArray(shader.VAO);
		shader.setFloat("x_offset", x_offset_value);
		shader.setFloat("y_offset", y_offset_value);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// --- End Drawing ---

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Clean up VAO, VBO, Program
	shader.Clean_Up();

	// Clean up
	glfwTerminate();
	return 0;
}

// Keeps window formatted for when user resizes the application
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

// Handles keyboard input
void Process_Input(GLFWwindow* window)
{
	// Closes window
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	// WASD movement
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		y_offset_value += 0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		y_offset_value -= 0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		x_offset_value += 0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		x_offset_value -= 0.01f;
	}

}
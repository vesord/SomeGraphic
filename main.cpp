#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>

float randFloat() {
	return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}

void key_callback(GLFWwindow * window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow * window = glfwCreateWindow(800, 600, "MUSHROOMS!", nullptr,
										   nullptr);
	if (window == nullptr) {
		std::cout << "No Hello, World!:(" << std::endl;
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cout << "No GLEW:(" << std::endl;
		return 1;
	}

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	glfwSetKeyCallback(window, key_callback);

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		glClearColor(randFloat(), randFloat(), randFloat(), 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}

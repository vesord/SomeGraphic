#define GLEW_STATIC
#include "GL/glew.h"
#include "glfw3.h"

#include "Utils/utils.h"
#include "Shaders/simpleVertexShader.h"

static const int windowWidth = 800;
static const int windowHeight = 600;

void initGlfwDefault() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
}

int main() {
	initGlfwDefault();

	GLFWwindow * window = glfwCreateWindow(windowWidth, windowHeight, "", NULL, NULL);
	if (!window)
		exit_fatal("Window creation failed\n");

	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f,
	};

	GLuint VBO;
	glGenBuffers(1, &VBO); // create buffer for vertices todo what is "1"?
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // binding VBO as GL_ARRAY_BUFFER
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // copying user data to buffer
	// GL_STATIC_DRAW - rarely change of data
	// GL_DYNAMIC_DRAW - frequently change
	// GL_STREAM_DRAW - each drawcall change

	GLuint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &simpleVertexShader, NULL);

	GLuint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		exit_fatal(infoLog);
	}
}
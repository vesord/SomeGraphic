//#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void exit_fatal(char * str) {
	write(2, str, strlen(str));
	exit(1);
}

float randFloat() {
	return (float)(rand()) / (float)(RAND_MAX);
}

//void checkIfShaderCompileOk(GLuint shader) {
//	GLuint success;
//	GLchar infoLog[512];
//	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
//	if (!success) {
//		glGetShaderInfoLog(shader, 512, NULL, infoLog);
//		exit_fatal(infoLog);
//	}
//}
//
//void checkIfProgramLinkOk(GLuint program) {
//	GLuint success;
//	GLchar infoLog[512];
//	glGetProgramiv(program, GL_LINK_STATUS, &success);
//	if (!success) {
//		glGetProgramInfoLog(program, 512, NULL, infoLog);
//		exit_fatal(infoLog);
//	}
//}


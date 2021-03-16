#ifndef FRAGMENTSHADERSIMPLE_H
#define FRAGMENTSHADERSIMPLE_H

const GLchar* fragmentShaderSourceSimple =
"#version 330 core\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color = vec4(0.8f, 0.8f, 0.0f, 1.0f);\n"
"}\n";

#endif //FRAGMENTSHADERSIMPLE_H

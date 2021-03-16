#ifndef VERTEXSHADERSIMPLE_H
#define VERTEXSHADERSIMPLE_H

const GLchar* vertexShaderSourceSimple =
"#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
"}\0";
#endif //VERTEXSHADERSIMPLE_H

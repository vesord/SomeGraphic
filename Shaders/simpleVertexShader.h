#ifndef SIMPLEVERTEXSHADER_H
#define SIMPLEVERTEXSHADER_H

const char * simpleVertexShader =
"#version 330 core\nlayout (location = 0) in vec3 position;\n\nvoid main() {\ngl_Position = vec4(position.x, position.y, position.z, 1.0);\n}";

#endif //SIMPLEVERTEXSHADER_H

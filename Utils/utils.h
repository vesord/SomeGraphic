#ifndef UTILS_H
#define UTILS_H

void exit_fatal(char * str);
float randFloat();
void checkIfShaderCompileOk(GLuint shader);
void checkIfProgramLinkOk(GLuint program);

#endif //UTILS_H

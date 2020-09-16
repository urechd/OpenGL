#include "ErrorHandle.h"

#include "GL/glew.h"

#include <iostream>

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* funcition, const char* file, int line)
{
    while (unsigned int error = glGetError())
    {
        std::cout << "[OpenGL Error] (" << error << "): " << funcition << " " << file << ":" << line << std::endl;
        return false;
    }

    return true;
}
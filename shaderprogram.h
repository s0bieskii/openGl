#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <GL/glew.h>
#include <string>

class ShaderProgram {
private:
    // Kompilacja pojedynczego shadera
    GLuint compileShader(GLenum type, const std::string& source);

    // Wczytanie pliku jako string
    std::string readFileAsString(const std::string& filePath);

public:
    // Tworzenie programu shadera
    GLuint createShaderProgram(const std::string& vertexSrc, const std::string& fragmentSrc);
};

#endif
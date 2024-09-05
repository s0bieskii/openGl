#include "shaderprogram.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

// Wczytanie pliku jako string
std::string ShaderProgram::readFileAsString(const std::string& filePath) {
    // Otwórz strumień pliku
    std::ifstream file(filePath);

    // Sprawdzenie, czy plik otworzył się poprawnie
    if (!file.is_open()) {
        throw std::runtime_error("Nie udało się otworzyć pliku: " + filePath);
    }

    // Wczytanie zawartości pliku do stringstream
    std::stringstream buffer;
    buffer << file.rdbuf();

    // Zamknięcie pliku
    file.close();

    // Zwrot zawartości pliku jako string
    return buffer.str();
}

// Kompilacja shadera
GLuint ShaderProgram::compileShader(GLenum type, const std::string& source) {
    GLuint shader = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    // Sprawdzenie poprawności kompilacji
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, sizeof(infoLog), nullptr, infoLog);
        std::cerr << "Błąd podczas kompilacji shadera: " << infoLog << std::endl;
    }

    return shader;
}

// Tworzenie programu shaderów
GLuint ShaderProgram::createShaderProgram(const std::string& vertexSrc, const std::string& fragmentSrc) {
    // Kompilacja vertex shadera
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, readFileAsString(vertexSrc));

    // Kompilacja fragment shadera
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, readFileAsString(fragmentSrc));

    // Tworzenie programu i przypinanie shaderów
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Sprawdzenie poprawności linkowania programu
    int success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, sizeof(infoLog), nullptr, infoLog);
        std::cerr << "Błąd podczas linkowania programu shaderów: " << infoLog << std::endl;
    }

    // Usunięcie shaderów po przypięciu do programu
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}
#pragma once


#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <GL/glew.h>

class Shader
{   
public:
    Shader(const std::string& shaderName);

    void Bind() const;

    void Unbind() const;

    virtual ~Shader();


private:
    static const unsigned int NUM_SHADER = 2;
    static GLuint CompileShader(const GLenum& shaderType, const std::string& source);
    static std::string LoadShaderSrc(const std::string& fileName);
    static void CheckShaderErr(GLuint shader, GLuint flag, bool isProgram, const std::string& errMsg);


    Shader(const Shader& other) = delete;
    Shader& operator=(const Shader& other) = delete;

    GLuint m_program;
    GLuint m_shaders[NUM_SHADER];

};

#endif
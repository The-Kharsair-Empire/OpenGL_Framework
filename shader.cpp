#include "shader.h"
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const std::string& shaderName)
{
    m_program = glCreateProgram();
    m_shaders[0] = CompileShader(GL_VERTEX_SHADER, LoadShaderSrc(shaderName + ".vs"));
    m_shaders[1] = CompileShader(GL_FRAGMENT_SHADER, LoadShaderSrc(shaderName + ".fs"));

    for (unsigned int i = 0; i < NUM_SHADER; i++) glAttachShader(m_program, m_shaders[i]);
    
    glLinkProgram(m_program);           CheckShaderErr(m_program, GL_LINK_STATUS, true, "Error Linking Shader Program");
    glValidateProgram(m_program);       CheckShaderErr(m_program, GL_LINK_STATUS, true, "Invalid Shader Program");

}

Shader::~Shader()
{
    for (unsigned int i = 0; i < NUM_SHADER; i++) 
    {
        glDetachShader(m_program, m_shaders[i]);
        glDeleteShader(m_shaders[i]);
    }

    glDeleteProgram(m_program);
}


void Shader::Bind() const
{
    glUseProgram(m_program);
}

void Shader::Unbind() const
{
    glUseProgram(0);
}


GLuint Shader::CompileShader(const GLenum& shaderType, const std::string& source)
{
    GLuint shader = glCreateShader(shaderType);
    if (shader == 0) std::cerr << "Error: Shader Creation" << std::endl;
    const GLchar* src = source.c_str();
    GLint l[1]; l[0] = source.length();
    glShaderSource(shader, 1, &src, l);
    glCompileShader(shader);

    CheckShaderErr(shader, GL_COMPILE_STATUS, false, "Error Compiling Shader");
        

    return shader;

}


std::string Shader::LoadShaderSrc(const std::string& fileName)
{   
    std::ifstream file(fileName);

    if (!file.is_open()) std::cerr << "unable to open shader source file: " << fileName << std::endl;

    std::stringstream ss;
    ss << file.rdbuf();
    file.close();

    return ss.str();
}   



void Shader::CheckShaderErr(GLuint shader, GLuint flag, bool isProgram, const std::string& errMsg)
{

    GLint success = 0;
  
    if (isProgram) glGetProgramiv(shader, flag, &success);
    else glGetShaderiv(shader, flag, &success);
  

    if (success == GL_FALSE)
    {
        int msgLen;
 
        if (isProgram) glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &msgLen);
        else glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &msgLen);

        char* message = (char*) alloca(msgLen * sizeof(char));

        if (isProgram) glGetProgramInfoLog(shader, msgLen, &msgLen, message);
        else glGetShaderInfoLog(shader, msgLen, &msgLen, message);
        
        std::cerr << errMsg << " : '" << message << "' " << std::endl;
    

       
    }


}


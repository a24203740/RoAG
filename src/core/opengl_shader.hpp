#ifndef SHADER_HPP
#define SHADER_HPP

#include <OpenGL/gl.h>
#include <glm/glm.hpp>

#include <string>

enum ShaderType {
    VERTEX = GL_VERTEX_SHADER,
    FRAGMENT = GL_FRAGMENT_SHADER
};

class Shader {
private:
    unsigned int shader_program_id;

    unsigned int LoadShader(std::string filepath, ShaderType type);
    unsigned int LoadVertexShader();
    unsigned int LoadFragmentShader();
    void BindProgram();
    void CheckCompileStatus(unsigned int shader_id, ShaderType type);
    void CheckLinkStatus();
public:
    void Init();
    void SetMat4(const std::string &name, const glm::mat4 &mat) const;
    void Use();
};

#endif
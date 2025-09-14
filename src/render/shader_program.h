//
// Created by Lecka on 12/09/2025.
//

#ifndef OPENGLOBJVIEWER_SHADER_H
#define OPENGLOBJVIEWER_SHADER_H

#include <glad/glad.h>

#include <string>
#include <glm/glm.hpp>
#include <fstream>
#include <sstream>
#include <iostream>



class ShaderProgram {
public:
    ShaderProgram(const std::string &vertexPath, const std::string &fragmentPath);

    explicit ShaderProgram(const std::string &shaderName) : ShaderProgram(shaderName + ".vert",
                                                                  shaderName + ".frag") {
    }

    void init();

    // use/activate the shader
    void use();

    // utility uniform functions
    void setBool(const std::string &name, bool value) const;

    void setInt(const std::string &name, int value) const;

    void setFloat(const std::string &name, float value) const;

    void setVec2(const std::string &name, const glm::vec2 &value) const;

    void setVec2(const std::string &name, float x, float y) const;

    void setVec3(const std::string &name, const glm::vec3 &value) const;

    void setVec3(const std::string &name, float x, float y, float z) const;

    void setVec4(const std::string &name, const glm::vec4 &value) const;

    void setVec4(const std::string &name, float x, float y, float z, float w) const;

    void setMat2(const std::string &name, const glm::mat2 &mat) const;

    void setMat3(const std::string &name, const glm::mat3 &mat) const;

    void setMat4(const std::string &name, const glm::mat4 &mat) const;

    void bindUniformBlock(const char* blockName, const GLuint binding) const {
        GLuint idx = glGetUniformBlockIndex(m_id, blockName);
        if (idx != GL_INVALID_INDEX) {
            glUniformBlockBinding(m_id, idx, binding);
        }
    }

    unsigned int getId() const { return m_id; }

private:
    static void checkCompileErrors(unsigned int shader, const std::string &type);

    static inline const std::string SHADER_DIR = "../assets/shaders/";

    unsigned int m_id;
    std::string m_vertPath, m_fragPath;
};


#endif //OPENGLOBJVIEWER_SHADER_H

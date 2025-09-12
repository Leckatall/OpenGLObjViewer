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


using str = std::string;

class Shader {
public:
    // the program ID
    unsigned int ID;

    // constructor reads and builds the shader
    Shader(const str &vertexPath, const str &fragmentPath);

    explicit Shader(const str &shaderName) : Shader(shaderName + ".vert",
                                                    shaderName + ".frag") {
    }

    // use/activate the shader
    void use() const;

    // utility uniform functions
    void setBool(const str &name, bool value) const;

    void setInt(const str &name, int value) const;

    void setFloat(const str &name, float value) const;

    void setVec2(const std::string &name, const glm::vec2 &value) const;

    void setVec2(const std::string &name, float x, float y) const;

    void setVec3(const std::string &name, const glm::vec3 &value) const;

    void setVec3(const std::string &name, float x, float y, float z) const;

    void setVec4(const std::string &name, const glm::vec4 &value) const;

    void setVec4(const std::string &name, float x, float y, float z, float w) const;

    void setMat2(const std::string &name, const glm::mat2 &mat) const;

    void setMat3(const std::string &name, const glm::mat3 &mat) const;

    void setMat4(const std::string &name, const glm::mat4 &mat) const;

private:
    static void checkCompileErrors(unsigned int shader, const std::string &type);

    static inline const str SHADER_DIR = "../shaders/";
};


#endif //OPENGLOBJVIEWER_SHADER_H

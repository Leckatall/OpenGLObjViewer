//
// Created by Lecka on 12/09/2025.
//

#ifndef OPENGLOBJVIEWER_WINDOW_H
#define OPENGLOBJVIEWER_WINDOW_H
#include <map>
#include <string>
#include "glad/glad.h"

#include "GLFW/glfw3.h"
#include "glm/vec2.hpp"


class Camera;

class Window {
public:
    explicit Window(const std::string& title, int width, int height);
    ~Window();

    bool initialise(Camera* camera);

    void mouseCallback(GLFWwindow* window, double xpos, double ypos) const;

    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

    bool isKeyPressed(int key) const;

    bool shouldClose() const;

    void swapBuffers() const;

    void pollEvents() const;

    glm::vec2 getSize() const;

    void setTitle(const std::string& title);

    GLFWwindow* getGLFWHandle() const;

    void close();

private:
    static void framebuffer_size_callback(GLFWwindow *window, int width, int height);

    std::string m_title;
    int m_width;
    int m_height;
    glm::vec2 m_center;
    GLFWwindow* m_window;
    Camera* m_camera;

};


#endif //OPENGLOBJVIEWER_WINDOW_H
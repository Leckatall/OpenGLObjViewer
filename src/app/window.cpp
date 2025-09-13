//
// Created by Lecka on 12/09/2025.
//

#include "window.h"

#include <iostream>

#include "../render/camera.h"


Window::Window(const std::string &title, const int width, const int height):
m_title(title),
m_width(width),
m_height(height),
m_window(nullptr),
m_camera(nullptr) {
    m_center = glm::vec2(width / 2, height / 2);
}

Window::~Window() {
    if (m_window) {
        glfwDestroyWindow(m_window);
    }
    glfwTerminate();
}

bool Window::initialise(Camera* camera) {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW." << std::endl;
        return false;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), NULL, NULL);
    if (!m_window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(m_window);
    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
    glfwSwapInterval(0);
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    // glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

    m_camera = camera;
    glfwSetWindowUserPointer(m_window, this);
    glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xpos, double ypos) {
        auto* instance = static_cast<Window*>(glfwGetWindowUserPointer(window));
        if (instance && instance->m_camera) {
            instance->mouseCallback(window, xpos, ypos);
        }
    });

    return true;
}

void Window::mouseCallback(GLFWwindow *window, double xpos, double ypos) const {
    m_camera->ProcessMouseMovement(xpos - m_center.x, m_center.y - ypos);
    glfwSetCursorPos(window, m_center.x, m_center.y);
}


bool Window::isKeyPressed(const int key) const {
    return glfwGetKey(m_window, key) == GLFW_PRESS;
}

bool Window::shouldClose() const {
    return glfwWindowShouldClose(m_window);
}

void Window::swapBuffers() const {
    glfwSwapBuffers(m_window);
}

void Window::pollEvents() const {
    glfwPollEvents();
}

glm::vec2 Window::getSize() const {
    return glm::vec2(m_width, m_height);
}

void Window::setTitle(const std::string &title) {
    m_title = title;
    glfwSetWindowTitle(m_window, m_title.c_str());
}

GLFWwindow * Window::getGLFWHandle() const {
    return m_window;
}

void Window::close() {
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

void Window::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

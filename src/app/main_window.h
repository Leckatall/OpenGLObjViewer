//
// Created by Lecka on 21/06/2025.
//

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <imgui.h>
#include "backends/imgui_impl_glfw.h"
#include <backends/imgui_impl_opengl3.h>

class MainWindow {
public:
    MainWindow(int w = 1200, int h = 800, const char* title = "OpenGL App");
    ~MainWindow();

    [[nodiscard]] bool shouldClose() const { return glfwWindowShouldClose(m_window); }
    void beginFrame();
    void endFrame();
    void renderUI();  // Override this for your specific UI

    [[nodiscard]] GLFWwindow* getWindow() const { return m_window; }

private:
    GLFWwindow* m_window;
    int m_width, m_height;
};


#endif //MAIN_WINDOW_H

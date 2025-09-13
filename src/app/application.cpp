//
// Created by Lecka on 13/09/2025.
//

#include "application.h"

Application::Application() : m_window{"FPS Trainer", 1600, 900} {
    m_camera = Camera();
    initialise();
}

void Application::run() {
    float lastTime = static_cast<float>(glfwGetTime());

    while (m_running && !m_window.shouldClose()) {
        const float currentTime = static_cast<float>(glfwGetTime());
        const float deltaTime = currentTime - lastTime;
        lastTime = currentTime;
        const auto window_size = m_window.getSize();
        glm::mat4 projection = glm::perspective(glm::radians(90.0f),
                                            window_size.x / window_size.y, 0.1f,
                                            100.0f);
        m_renderer.setViewProjectionMatrix(projection);

        handleInput(deltaTime);
        update(deltaTime);
        render();

        m_window.swapBuffers();
        m_window.pollEvents();
    }
    m_window.close();
}

void Application::initialise() {
    if (!m_window.initialise(&m_camera)) {
        std::cerr << "Failed to initialize the window!" << std::endl;
        m_running = false;
    }

    if (!m_renderer.initialise()) {
        std::cerr << "Failed to initialize the renderer!" << std::endl;
        m_running = false;
    }
    m_world.initialise();
}

void Application::handleInput(const float deltaTime) {
    if (m_window.isKeyPressed(GLFW_KEY_ESCAPE))
        m_running = false;

    for (const auto &[key, direction]: moveKeys) {
        if (m_window.isKeyPressed(key))
            m_camera.ProcessKeyboard(direction, deltaTime);
    }
}

void Application::update(float deltaTime) {
    m_world.update(deltaTime);
}

void Application::render() {
    m_renderer.clear();
    m_world.render(m_renderer);
}

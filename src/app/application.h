//
// Created by Lecka on 13/09/2025.
//

#ifndef OPENGLOBJVIEWER_APPLICATION_H
#define OPENGLOBJVIEWER_APPLICATION_H
#include "window.h"
#include "../render/renderer.h"
#include "../Game/world.h"


class Application {
public:
    Application();
    ~Application() = default;

    // Run the main application loop
    void run();

private:
    void initialise();
    void handleInput(float deltaTime);
    void update(float deltaTime);
    void render();

    Window m_window;
    Renderer m_renderer;
    World m_world;
    Camera m_camera;

    std::map<int, Camera_Movement> moveKeys = {
        {GLFW_KEY_W, Camera_Movement::FORWARD},
        {GLFW_KEY_S, Camera_Movement::BACKWARD},
        {GLFW_KEY_A, Camera_Movement::LEFT},
        {GLFW_KEY_D, Camera_Movement::RIGHT}
    };

    bool m_running = true;
};


#endif //OPENGLOBJVIEWER_APPLICATION_H
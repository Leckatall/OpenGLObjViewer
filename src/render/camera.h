//
// Created by Lecka on 12/09/2025.
//

#ifndef OPENGLOBJVIEWER_CAMERA_H
#define OPENGLOBJVIEWER_CAMERA_H


#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "camera_data.h"
#include "glm/detail/type_quat.hpp"

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum class Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

// Default camera values
constexpr float YAW = -90.0f;
constexpr float PITCH = 0.0f;
constexpr float SPEED = 5.0f;
constexpr float SENSITIVITY = 0.1f;
constexpr float ZOOM = 90.0f;


// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera {
public:
    // constructor with vectors
    explicit Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
                    float yaw = YAW, float pitch = PITCH);

    // constructor with scalar values
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw,
           float pitch);

    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 getViewMatrix() const;

    // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void ProcessKeyboard(Camera_Movement direction, float deltaTime);

    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(float xoffset, float yoffset);

    // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseScroll(float yoffset);

    [[nodiscard]] glm::vec3 getUp() const { return glm::normalize(glm::cross(getRight(), m_front)); }

    [[nodiscard]] glm::vec3 getRight() const { return glm::normalize(glm::cross(m_front, m_world_up)); }

    [[nodiscard]] glm::vec3 getFront() const { return m_front; }

    [[nodiscard]] glm::vec3 getPos() const { return m_pos; }

    [[nodiscard]] glm::vec3 getWorldUp() const { return m_world_up; }

    void setPosition(const glm::vec3& p) { m_pos = p; }

    void setPerspective(const float fov, const float aspect, const float near, const float far) { m_perspective = glm::perspective(glm::radians(fov), aspect, near, far);}

    CameraData getCameraData() const {
        // Basis from orientation (OpenGL convention: forward = -Z)
        return {getViewMatrix(), m_perspective, m_pos};
    }

    // camera options
    float MovementSpeed;
    float MouseSensitivity;

private:
    // calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors();

    // camera Attributes
    glm::vec3 m_pos;
    glm::vec3 m_front;
    glm::vec3 m_world_up;
    glm::vec3 m_lens;
    // TODO: Un-hardcode the aspect ratio and FOV
    glm::mat4 m_perspective = glm::perspective(glm::radians(90.0f), 1600.0f/900.0f, 0.1f, 100.0f);
    // euler Angles
    float m_yaw;
    float m_pitch;
};
#endif


#endif //OPENGLOBJVIEWER_CAMERA_H

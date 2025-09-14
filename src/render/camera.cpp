//
// Created by Lecka on 12/09/2025.
//

#include "camera.h"

#include "glm/gtc/quaternion.hpp"

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    : m_pos(position),
      m_front(glm::vec3(0.0f, 0.0f, -1.0f)),
      m_world_up(up),
      m_yaw(yaw), m_pitch(pitch),
      MovementSpeed(SPEED),
      MouseSensitivity(SENSITIVITY) {
    updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw,
               float pitch)
    : m_front(glm::vec3(0.0f, 0.0f, -1.0f)),
      MovementSpeed(SPEED),
      MouseSensitivity(SENSITIVITY) {
    m_pos = glm::vec3(posX, posY, posZ);
    m_world_up = glm::vec3(upX, upY, upZ);
    m_yaw = yaw;
    m_pitch = pitch;
    updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(m_pos, m_pos + m_front, getUp());
}

void Camera::ProcessKeyboard(const Camera_Movement direction, const float deltaTime) {
    const float velocity = MovementSpeed * deltaTime;
    glm::vec3 moveDir;
    switch (direction) {
        case Camera_Movement::FORWARD: moveDir = m_front;
            break;
        case Camera_Movement::BACKWARD: moveDir = -m_front;
            break;
        case Camera_Movement::LEFT: moveDir = -getRight();
            break;
        case Camera_Movement::RIGHT: moveDir = getRight();
            break;
        case Camera_Movement::UP: moveDir = getUp();
            break;
        case Camera_Movement::DOWN: moveDir = -getUp();
            break;
    }
    m_pos += moveDir * velocity;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset) {
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    m_yaw += xoffset;
    m_pitch += yoffset;
    m_pitch = glm::clamp(m_pitch, -89.0f, 89.0f);
    // update Front, Right and Up Vectors using the updated Euler angles
    updateCameraVectors();
}


void Camera::updateCameraVectors() {
    // calculate the new Front vector
    glm::vec3 front;
    front.x = cosf(glm::radians(m_yaw)) * cosf(glm::radians(m_pitch));
    front.y = sinf(glm::radians(m_pitch));
    front.z = sinf(glm::radians(m_yaw)) * cosf(glm::radians(m_pitch));
    m_front = glm::normalize(front);
}

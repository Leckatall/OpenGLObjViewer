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
      MouseSensitivity(SENSITIVITY), m_fov(ZOOM) {
    updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw,
               float pitch) : m_front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY),
                              m_fov(ZOOM) {
    m_pos = glm::vec3(posX, posY, posZ);
    m_world_up = glm::vec3(upX, upY, upZ);
    m_yaw = yaw;
    m_pitch = pitch;
    updateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix() {
    return glm::lookAt(m_pos, m_pos + m_front, m_up);
}

void Camera::ProcessKeyboard(const Camera_Movement direction, const float deltaTime) {
    const float velocity = MovementSpeed * deltaTime;
    const auto right = glm::normalize(glm::cross(m_front, m_world_up));
    glm::vec3 moveDir;
    switch(direction) {
        case FORWARD:  moveDir = m_front; break;
        case BACKWARD: moveDir = -m_front; break;
        case LEFT:     moveDir = -right; break;
        case RIGHT:    moveDir = right; break;
    }
    m_pos += moveDir * velocity;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch) {
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    m_yaw += xoffset;
    m_pitch += yoffset;
    m_pitch = glm::clamp(m_pitch + yoffset, -89.0f, 89.0f);
    // update Front, Right and Up Vectors using the updated Euler angles
    updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset) {
    m_fov -= yoffset;
    if (m_fov < 1.0f)
        m_fov = 1.0f;
    if (m_fov > 90.0f)
        m_fov = 90.0f;
}

void Camera::updateCameraVectors() {
    // calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    front.y = sin(glm::radians(m_pitch));
    front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_front = glm::normalize(front);

}

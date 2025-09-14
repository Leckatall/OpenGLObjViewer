//
// Created by Lecka on 14/09/2025.
//

#ifndef OPENGLOBJVIEWER_CAMERA_DATA_H
#define OPENGLOBJVIEWER_CAMERA_DATA_H
#include <glm/glm.hpp>

struct CameraData {
    glm::mat4 view, proj;
    glm::vec3 cameraPosWS;
};

#endif //OPENGLOBJVIEWER_CAMERA_DATA_H
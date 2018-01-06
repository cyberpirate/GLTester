//
// Created by joevi on 1/6/2018.
//

#ifndef GLTESTER_GLMUTILS_H
#define GLTESTER_GLMUTILS_H

#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

float getAngleToTop(glm::vec3 vec) {

    glm::vec3 norm = glm::normalize(vec);

    float dot = glm::dot(norm, glm::vec3(0, 1, 0));

    return acosf(dot);
}

#endif //GLTESTER_GLMUTILS_H


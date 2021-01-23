#pragma once

#include <glm/glm.hpp>

class Ray {
    glm::vec3 m_origin;
    glm::vec3 m_direction;

    public:
    Ray(glm::vec3 origin, glm::vec3 direction)
        : m_origin(origin),
          m_direction(glm::normalize(direction)) {}

    glm::vec3& origin()    { return m_origin; }
    glm::vec3& direction() { return m_direction; }

    glm::vec3 closest_point_on_ray(glm::vec3 point) {
        glm::vec3 v = point - m_origin;
        float d = glm::dot(v, m_direction);
        return m_origin + m_direction * d;
    }
};

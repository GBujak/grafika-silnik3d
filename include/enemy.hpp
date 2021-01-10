#pragma once

#include <glm/glm.hpp>

class Enemy {
    glm::vec3 m_position;

    public:
    Enemy(glm::vec3 position): m_position(position) {}
    void update(glm::vec3 player_position); 
    glm::vec3 pos();
};

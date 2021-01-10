#pragma once

#include <glm/glm.hpp>
#include <shader.hpp>

class Renderer {
    Shader m_enemy_shader;

    public:
    Renderer(Shader enemy_shader): m_enemy_shader(enemy_shader) {}

    void draw_enemy(glm::vec3 enemy_pos, glm::vec3 player_pos);
};

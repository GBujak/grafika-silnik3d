#pragma once

#include <glm/glm.hpp>
#include <shader.hpp>
#include <camera.hpp>
#include <enemy.hpp>

class Renderer {
    Shader m_enemy_shader;
    Camera& m_camera;

    public:
    Renderer(Shader enemy_shader, Camera& camera)
        : m_enemy_shader(enemy_shader),
          m_camera(camera) {}

    void draw_enemy(Enemy& enemy);
};

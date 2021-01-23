#pragma once

#include <glm/glm.hpp>
#include <shader.hpp>
#include <camera.hpp>
#include <mesh.hpp>
#include <enemy.hpp>
#include <globals.hpp>

class Renderer {
    Shader m_enemy_shader;
    Mesh m_enemy_mesh;

    Camera& m_camera;

    public:
    Renderer(Shader enemy_shader, Mesh enemy_mesh, Camera& camera)
        : m_enemy_shader(enemy_shader),
          m_enemy_mesh(enemy_mesh),
          m_camera(camera) {

    m_enemy_shader.use();
    auto projection = glm::perspective(glm::radians(90.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
    m_enemy_shader.setMat4("projection", projection);

  }

    void draw_enemy(Enemy& enemy);
};

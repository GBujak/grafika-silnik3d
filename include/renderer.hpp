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

    Shader m_floor_shader;
    Mesh m_floor_mesh;

    Shader m_crosshair_shader;
    Mesh m_crosshair_mesh;

    Camera& m_camera;

    public:
    Renderer(Shader enemy_shader, Mesh enemy_mesh, Shader floor_shader, Mesh floor_mesh, Shader crosshair_shader, Mesh crosshair_mesh, Camera& camera)
        : m_enemy_shader(enemy_shader),
          m_enemy_mesh(enemy_mesh),
          m_floor_shader(floor_shader),
          m_floor_mesh(floor_mesh),
          m_crosshair_shader(crosshair_shader),
          m_crosshair_mesh(crosshair_mesh),
          m_camera(camera) {

          auto projection = glm::perspective(glm::radians(90.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);

          m_enemy_shader.use();
          m_enemy_shader.setMat4("projection", projection);
          m_floor_shader.use();
          m_floor_shader.setMat4("projection", projection);
          m_crosshair_shader.use();
          m_crosshair_shader.setVec4("color", glm::vec4(0.5, 0.5, 0.8, 1.0));
    }

    void draw_enemy(Enemy& enemy);
    void draw_floor();
    void draw_crosshair(bool can_shoot);
};

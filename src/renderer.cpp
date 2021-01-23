#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include <renderer.hpp>
#include <globals.hpp>

void Renderer::draw_enemy(Enemy& enemy) {
    m_enemy_shader.use();

    // view
    auto view = m_camera.GetViewMatrix();
    m_enemy_shader.setMat4("view", view);

    // model
    auto model = glm::mat4(1.0f);
    model = glm::translate(model, enemy.pos());
    m_enemy_shader.setMat4("model", model);

    // color
    m_enemy_shader.setVec4("color", enemy.color());

    m_enemy_mesh.use();
    m_enemy_mesh.draw();
}

void Renderer::draw_floor() {
    m_floor_shader.use();
    
    auto floor_pos = m_camera.pos();
    floor_pos.y -= 2.0f;

    auto model = glm::mat4(1.0f);
    model = glm::translate(model, floor_pos);
    m_floor_shader.setMat4("model", model);

    m_floor_shader.setMat4("view", m_camera.GetViewMatrix());
    m_floor_mesh.use();
    m_floor_mesh.draw();
}

void Renderer::draw_crosshair(bool can_shoot) {

    auto color = glm::vec4(0.5, 0.5, 0.8, 1.0);

    if (!can_shoot) {
        color.b = 0.5;
        color.r = 1.0f;
    }

    m_crosshair_shader.use();
    m_crosshair_shader.setVec4("color", color);
    m_crosshair_mesh.use();
    m_crosshair_mesh.draw();
}

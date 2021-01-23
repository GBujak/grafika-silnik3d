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

    m_enemy_mesh.use();
    m_enemy_mesh.draw();
}

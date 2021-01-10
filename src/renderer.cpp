#include <renderer.hpp>

void Renderer::draw_enemy(glm::vec3 enemy_pos, glm::vec3 player_pos) {
    auto look_direction = glm::normalize(player_pos - enemy_pos);
    
    // TODO: bind VAO

    auto model = glm::mat4(1.0f);

}

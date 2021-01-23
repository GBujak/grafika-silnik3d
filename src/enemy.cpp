#include <enemy.hpp>
#include <glm/glm.hpp>
#include <glm/geometric.hpp>
#include <iostream>

Enemy::Enemy(glm::vec3 position, glm::vec3 player_position, AiVariant ai_variant) {
    this->m_position           = position;
    this->m_no_offset_position = position;
    this->m_ai_variant         = ai_variant;

    // Dzięki temu wszystkie warianty mają taki sam konstruktor
    if (m_ai_variant == AiVariant::CircularMovement) {
        auto player_vec = player_position - position;
        m_player_distance = glm::length(player_vec);
        m_radian_position = asinf(player_vec.x / m_player_distance);
    }
}

void Enemy::update(float time_diff, glm::vec3 player_position) {
    auto time = (float) glfwGetTime();
    auto player_vec = player_position - m_position;
    auto player_vec_normal = glm::normalize(player_vec);

    if (m_ai_variant == AiVariant::StraightLineMovement) {
        m_position += player_vec_normal * time_diff * EnemyConstants::APPROACH_SPEED;
    }

    if (m_ai_variant == AiVariant::SinusoidalMovement) {
        m_position += player_vec_normal * time_diff * EnemyConstants::APPROACH_SPEED;
        auto cross = glm::normalize(glm::cross(player_vec, glm::vec3(0.0, 1.0, 0.0)));
        auto cross_multiplier = sinf(time / EnemyConstants::SINUS_FREQUENCY) * EnemyConstants::SINUS_MULTIPLIER;
        m_position += cross * cross_multiplier;
    }

    if (m_ai_variant == AiVariant::CircularMovement) {
        m_radian_position += EnemyConstants::RADIAL_SPEED * time_diff;
        m_player_distance -= EnemyConstants::APPROACH_SPEED * time_diff;
        // std::cout << "----------" << std::endl;
        // std::cout << m_player_distance << std::endl;
        // std::cout << m_radian_position << std::endl;
        float x = sinf(m_radian_position) * m_player_distance;
        float z = cosf(m_radian_position) * m_player_distance;
        // std::cout << x << " - " << z << std::endl;
        m_position = player_position + glm::vec3(x, 1.0, z);
        // std::cout << m_position.x << "-" << m_position.y << "-" << m_position.z << std::endl;
    }
}

glm::vec3 Enemy::pos() {
    return m_position;
}

glm::vec4 Enemy::model_matrix() {
    return glm::vec4(pos(), 1.0f); // TODO: Obrót modelu
}

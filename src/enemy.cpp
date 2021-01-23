#include <enemy.hpp>
#include <glm/glm.hpp>
#include <glm/geometric.hpp>
#include <glm/trigonometric.hpp>
#include <iostream>
#include <math.h>
#include <unordered_map>


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

Enemy::Enemy(float degrees, float radius, glm::vec3 player_position) {
    auto rads = glm::radians(degrees);
    glm::vec3 position = player_position;
    position.x += sinf(rads) * radius;
    position.y += rand() % 3;
    position.z += cosf(rads) * radius;
    m_position = position;
    m_no_offset_position = position;

    m_radian_position = rads;
    m_player_distance = radius;

    auto ai = rand() % 3;

    switch (ai) {
        case 0: m_ai_variant = AiVariant::StraightLineMovement; break;
        case 1: m_ai_variant = AiVariant::SinusoidalMovement; break;
        case 2: m_ai_variant = AiVariant::CircularMovement; break;
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
        float x = sinf(m_radian_position) * m_player_distance;
        float y = tanf(glm::radians(45.0f)) * m_player_distance;
        float z = cosf(m_radian_position) * m_player_distance;
        m_position = player_position + glm::vec3(x, y, z);
    }
}

glm::vec3 Enemy::pos() {
    return m_position;
}

glm::vec4 Enemy::model_matrix() {
    return glm::vec4(pos(), 1.0f); // TODO: Obrót modelu
}

const std::unordered_map<Enemy::AiVariant, glm::vec4> Enemy::AI_COLOR_MAP {
    {AiVariant::StraightLineMovement, glm::vec4(0.192, 0.439, 0.871, 1.0)},
    {AiVariant::SinusoidalMovement,   glm::vec4(0.192, 0.871, 0.282, 1.0)},
    {AiVariant::CircularMovement,     glm::vec4(0.871, 0.620, 0.192, 1.0)},
};

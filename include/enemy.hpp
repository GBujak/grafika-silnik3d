#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/trigonometric.hpp>

namespace EnemyConstants {
    constexpr float ENEMY_RADIUS     = 1.0f;               // Do wykrywania kolizji

    constexpr float APPROACH_SPEED   = 0.5f;               // Prędkość zbliżania się do gracza w prostej linii
    constexpr float RADIAL_SPEED     = glm::radians(30.0f); // Prędkość kątowa okrążania gracza

    constexpr float SINUS_MULTIPLIER = 0.06f;               // Wysokość fali w ruchu sinusoidalnym
    constexpr float SINUS_FREQUENCY  = 0.5f;               // Częstotliwość fali
};

enum class AiVariant {
    StraightLineMovement,
    SinusoidalMovement,
    CircularMovement
};

class Enemy {
    public:
    enum class AiVariant {
        StraightLineMovement,
        SinusoidalMovement,
        CircularMovement
    };
    
    private:
    glm::vec3 m_position;
    AiVariant m_ai_variant;

    // SinusoidalMovement

    // Pozycja bez wychylenia na bok (dzięki temu
    // przeciwnik nie zbliża się szybciej do
    // gracza, gdy wychylenie = 0)
    glm::vec3 m_no_offset_position;

    // CircularMovement
    float m_radian_position;
    float m_player_distance;

    public:
    Enemy(glm::vec3 position, glm::vec3 player_position, AiVariant ai_variant);
    Enemy(float degree, float radius, glm::vec3 player_position);

    void update(float time_diff, glm::vec3 player_position); 
    glm::vec3 pos();
    glm::vec4 model_matrix();
};

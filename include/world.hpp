#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <ray.hpp>
#include <enemy.hpp>
#include <optional>

class World {
    std::vector<Enemy> m_enemies;

    float m_last_spawn_time = 0.0;
    unsigned m_spawn_count = 0;

    public:
    std::vector<Enemy>& enemies() { return m_enemies; }

    // Zwraca przetrwane fale wrogów, gdy gra się skończyła, -1, gdy gra trwa
    int update(float absolute_time, float time_diff, glm::vec3 player_pos);

    void handle_ray(Ray ray);
};

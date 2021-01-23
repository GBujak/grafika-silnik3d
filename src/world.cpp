#include <glm/geometric.hpp>
#include <iostream>
#include <world.hpp>

void World::update(float absolute_time, float time_diff, glm::vec3 player_pos) {
    auto not_spawned_time = absolute_time - m_last_spawn_time;
    if (not_spawned_time > 5.0) {
        auto degrees = rand() % 360;
        auto radius = 5 + rand() % 5;
        m_enemies.push_back(Enemy(degrees, radius, player_pos));
        m_last_spawn_time = absolute_time;
    }

    for (auto& enemy: m_enemies)
        enemy.update(time_diff, player_pos);
}

void World::handle_ray(Ray ray) {
    int killed_enemy = -1;
    float killed_enemy_distance = 99999;

    for (int i = 0; i < (int) m_enemies.size(); i++) {
        auto& enemy = m_enemies[i];
        auto closest_point = ray.closest_point_on_ray(enemy.pos());
        auto distance = glm::length(closest_point - enemy.pos());
        if (distance < 1.0f) {
            auto origin_distance = glm::length(ray.origin() - enemy.pos());
            if (origin_distance < killed_enemy_distance) {
                killed_enemy_distance = origin_distance;
                killed_enemy = i;
            }
        }
    }

    if (killed_enemy != -1)
        m_enemies.erase(m_enemies.begin() + killed_enemy);
}

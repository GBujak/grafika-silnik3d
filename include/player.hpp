#pragma once

#include <camera.hpp>
#include <world.hpp>
#include <iostream>

constexpr float SHOT_RECOVERY = 1.0;

class Player {
    Camera m_camera;

    float m_last_shot_time = 0.0;

    public:
    Camera& cam() { return m_camera; }

    void try_shoot(float absolute_time, World& world) {
        if (absolute_time - m_last_shot_time >= SHOT_RECOVERY) {
        std::cout << "try shoot" << std::endl;
            world.handle_ray(Ray(m_camera.pos(), m_camera.aim_vector()));
            m_last_shot_time = absolute_time;
        }            
    }
        
};

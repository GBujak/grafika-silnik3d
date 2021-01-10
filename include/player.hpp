#pragma once

#include <camera.hpp>

class Player {
    Camera m_camera;

    public:
    Camera& cam() { return m_camera; }
};

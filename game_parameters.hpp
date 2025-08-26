#pragma once

struct Parameters{
    static constexpr int game_width = 700;
    static constexpr int game_height = 700;
    // gravitational pull
    static constexpr float g = -9.8f;
    // 1 sfml unit = 30 physics units
    static constexpr float physics_scale = 30.f;
    static constexpr float physics_scale_inv = 1.0f / physics_scale;
    // Magic numbers for accuracy of physics simulation
    static constexpr int velocityIterations = 6;
    static constexpr int positionIterations = 2;

    static constexpr int sub_step_count = 4;
    static constexpr float time_step = 0.017f; 
};
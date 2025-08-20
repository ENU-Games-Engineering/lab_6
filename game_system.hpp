#pragma once
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>


struct GameSystem{
  // gravitational pull
  constexpr static float g = -9.8f;
  // 1 sfml unit = 30 physics units
  constexpr static float physics_scale = 30.f;
  constexpr static float physics_scale_inv = 1.0f / physics_scale;
  // Magic numbers for accuracy of physics simulation
  constexpr static int velocityIterations = 6;
  constexpr static int positionIterations = 2;

  constexpr static int sub_step_count = 4;
  constexpr static float time_step = 0.017f; // ~ 1/60 second or 60 fps

  static b2WorldId world_id;
  static std::vector<b2BodyId> bodies;
  static std::vector<std::shared_ptr<sf::RectangleShape>> sprites;

  static void init();
  static void load();
  static void clean();
  static void update(sf::RenderWindow &window);
  static void render(sf::RenderWindow &window);
};

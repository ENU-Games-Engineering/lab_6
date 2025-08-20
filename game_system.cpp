#include <iostream>
#include "game_system.hpp"
#include "game_parameters.hpp"
#include "b2_utils.hpp"

namespace b2 = box2d;

std::vector<b2BodyId> GameSystem::bodies;
std::vector<std::shared_ptr<sf::RectangleShape>> GameSystem::sprites;
b2WorldId GameSystem::world_id;


void GameSystem::init() {
  // Construct a world, which holds and simulates the physics bodies.
  b2WorldDef world_def = b2DefaultWorldDef();
  world_def.gravity = b2Vec2({0.0f, g});  
  world_id = b2CreateWorld(&world_def);

  // Create Boxes
  for (int i = 1; i < 11; ++i) {
    // Create SFML shapes for each box
    std::shared_ptr<sf::RectangleShape> s = std::make_shared<sf::RectangleShape>();
    s->setPosition(sf::Vector2f(i * (game_width / 12.f), game_height * .7f));
    s->setSize(sf::Vector2f(50.0f, 50.0f));
    s->setOrigin(sf::Vector2f(25.0f, 25.0f));
    s->setFillColor(sf::Color::White);
    sprites.push_back(s);
    
    // Create a dynamic physics body for the box
    b2BodyId b = b2::create_physics_box(world_id, true, s);
    // Give the box a spin
    b2Body_ApplyAngularImpulse(b,5.0f, true);
    bodies.push_back(b);
  }

  sf::Vector2f walls[] = {
      // Top
      sf::Vector2f(game_width * .5f, 5.f), sf::Vector2f(game_width, 10.f),
      // Bottom
      sf::Vector2f(game_width * .5f, game_height - 5.f), sf::Vector2f(game_width, 10.f),
      // left
      sf::Vector2f(5.f, game_height * .5f), sf::Vector2f(10.f, game_height),
      // right
      sf::Vector2f(game_width - 5.f, game_height * .5f), sf::Vector2f(10.f, game_height)
  };

  // Build Walls
  for (int i = 0; i < 7; i += 2) {
      // Create SFML shapes for each wall
      std::shared_ptr<sf::RectangleShape> s = std::make_shared<sf::RectangleShape>();
      s->setPosition(walls[i]);
      s->setSize(walls[i+1]);
      s->setOrigin(walls[i+1]/2.f);
      s->setFillColor(sf::Color::White);
      sprites.push_back(s);
      // Create a static physics body for the wall
      b2BodyId b = b2::create_physics_box(world_id,false,s);
      bodies.push_back(b);
  }

}
void GameSystem::load() {
}

void GameSystem::clean(){
  for(std::shared_ptr<sf::RectangleShape> &shape: sprites)
    shape.reset();
  sprites.clear();
  
  for(b2BodyId body: bodies)
    b2DestroyBody(body);
  bodies.clear();
  b2DestroyWorld(world_id);
}

void GameSystem::update(sf::RenderWindow &window){
  static sf::Clock clock;
  float dt = clock.restart().asSeconds();
  sf::Event event;
  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
        window.close();
        return;
    }
  }
  // Step Physics world by time_step
  b2World_Step(world_id,time_step,sub_step_count);

  for (int i = 0; i < bodies.size(); ++i) {
    // Sync Sprites to physics position
    sprites[i]->setPosition(b2::invert_height(b2::bv2_to_sv2(b2Body_GetPosition(bodies[i]))));
    // Sync Sprites to physics Rotation
    sprites[i]->setRotation((180 / M_PI) * asin(b2Body_GetRotation(bodies[i]).s));
  }
  sf::sleep(sf::seconds(time_step));
}

void GameSystem::render(sf::RenderWindow &window){
  for(std::shared_ptr<sf::RectangleShape> &shape: sprites){
    window.draw(*(shape.get()));
  }
}

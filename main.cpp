#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "game_parameters.hpp"
#include "game_system.hpp"

sf::Texture spritesheet;

int main(){
  sf::RenderWindow window(sf::VideoMode({game_width, game_height}), "SPACE Invaders");
  GameSystem::load();
  GameSystem::init();
	while(window.isOpen()){
    window.clear();
    GameSystem::update(window);
    GameSystem::render(window);
    //Wait for Vsync
    window.display();
  }
  GameSystem::clean();
  return 0;
}

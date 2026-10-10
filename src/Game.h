
#ifndef SFML_GAME_H
#define SFML_GAME_H

#include <SFML/Graphics.hpp>
#include "Utility.h"
#include "Passport.h"
#include <SFML/Window/Cursor.hpp>
#include "GameStateManager.h"

class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool init();
  void update(float dt);
  void render();
  
  void mouseButtonPressed(const sf::Event::MouseButtonPressed* event);
  bool clickCheck(sf::Vector2f mouse_pos, sf::FloatRect sprite);
  void mouseButtonReleased(const sf::Event::MouseButtonReleased* event);
  void keyPressed(const sf::Event::KeyPressed* event);
  void keyReleased(const sf::Event::KeyReleased* event);
  void mouseMoved(const sf::Event::MouseMoved* event);
  void handleEvent(const sf::Event& event, sf::RenderWindow& window);

 private:
  sf::RenderWindow& window;


  GameStateManager gs_manager;
  //sf::Sprite bird = sf::Sprite(bird_texture);
 


  

};

#endif // SFML_GAME_H

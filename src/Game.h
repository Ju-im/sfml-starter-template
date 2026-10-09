
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
  void dragSprite(sf::Sprite* sprite);
  void mouseButtonPressed(const sf::Event::MouseButtonPressed* event);
  bool clickCheck(sf::Vector2f mouse_pos, sf::FloatRect sprite);
  void mouseButtonReleased(const sf::Event::MouseButtonReleased* event);
  void keyPressed(const sf::Event::KeyPressed* event);
  void keyReleased(const sf::Event::KeyReleased* event);
  void mouseMoved(const sf::Event::MouseMoved* event);
  void handleEvent(const sf::Event& event, sf::RenderWindow& window);

 private:
  sf::RenderWindow& window;
  sf::Texture backgroundTexture{ "../Data/Images/WhackaMole Worksheet/background.png" };
  sf::Texture reject_button_texture{ "../Data/Images/Critter Crossing/reject button.png" };
  sf::Texture reject{ "../Data/Images/Critter Crossing/reject.png" };
  sf::Sprite background{ backgroundTexture };
  sf::Texture* animals = new sf::Texture[3];
  sf::Texture* passport_textures = new sf::Texture[3];
  sf::Sprite* character;
  GameStateManager gs_manager;

  sf::Sprite reject_button{ reject_button_texture };
  sf::Sprite reject_stamp{ reject };
  sf::Vector2f drag_offset{ 0.0,0.0 };
  sf::Font font{ "../Data/Fonts/OpenSans-Bold.ttf" };
  sf::Text text{ font };
  bool test{ true };
  //sf::Sprite bird = sf::Sprite(bird_texture);
 
  sf::Sprite* dragged = nullptr;
  Passport passport;

  

};

#endif // SFML_GAME_H

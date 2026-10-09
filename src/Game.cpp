
#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL)); //seeds random number generator with the current time
}

Game::~Game()
{
	delete[] animals;
	delete[] passport_textures;
	delete character;

}

// We call this once after the game class is instantiated
bool Game::init()
{
	passport.init();
	animals[0].loadFromFile("../Data/Images/Critter Crossing/elephant.png");
	animals[1].loadFromFile("../Data/Images/Critter Crossing/moose.png");
	animals[2].loadFromFile("../Data/Images/Critter Crossing/penguin.png");
	gs_manager.init();
	
	passport_textures[0].loadFromFile("../Data/Images/Critter Crossing/elephant passport.png");
	passport_textures[1].loadFromFile("../Data/Images/Critter Crossing/moose passport.png");
	passport_textures[2].loadFromFile("../Data/Images/Critter Crossing/penguin passport.png");

	character = new sf::Sprite(animals[0]);
	character->setPosition({ 500,300 });
	passport.getSprite()->setPosition({ 300,300 });
  return true;
}

// Update runs after event polling and before rendering
// use it for everything that needs to update between frames
void Game::update(float dt)
{
	if (dragged != nullptr) {

		dragSprite(dragged);
	}
	gs_manager.update(dt);
	
}
// for the queue i could make a square greyed out just bobbing up and down
// Runs after update, use it to tell the window what to draw this frame
void Game::render()
{
	gs_manager.render(window);
	
	

}


void Game::dragSprite(sf::Sprite* sprite) {
	
	


	if (sprite != nullptr) {
		
		sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
		sf::Vector2f mouse_posf = static_cast<sf::Vector2f>(mouse_pos);
		
	
		sf::Vector2f drag_pos = mouse_posf - drag_offset;
		sprite->setPosition({ drag_pos.x,drag_pos.y });
	}

}
//Called by event polling when a MouseButtonPressed event is found
void Game::mouseButtonPressed(const sf::Event::MouseButtonPressed* event)
{
	// Event contains mouse position and which button was clicked

	// Don't need to extract position to a variable like this, this is just to show you it's a Vector2i
	sf::Vector2i position = event->position;
	sf::Vector2f mouse_posf = static_cast<sf::Vector2f>(position);
	gs_manager.mouseButtonPressed(event);
	// You can tell which button was pressed by comparing it to SFML's definitions of mouse buttons
	if (event->button == sf::Mouse::Button::Left)
	{
		//Left mouse button was pressed
		

		if (clickCheck(mouse_posf, character->getGlobalBounds())) {
			
			drag_offset = mouse_posf - character->getPosition();

			dragged = character;

		}

		if (clickCheck(mouse_posf, passport.getSprite()->getGlobalBounds())) {
			
			drag_offset = mouse_posf - passport.getSprite()->getPosition();

			dragged = passport.getSprite();

		}
		
	}
}

bool Game::clickCheck(sf::Vector2f mouse_pos, sf::FloatRect sprite) {
	
	return sprite.contains(mouse_pos);

}
void Game::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
	gs_manager.handleEvent(event, window);
}
//Called by event polling when a MouseButtonReleased event is found
void Game::mouseButtonReleased(const sf::Event::MouseButtonReleased* event)
{
	//Works the same as MouseButtonPressed
	if (event->button == sf::Mouse::Button::Left)
	{
		dragged = nullptr;
		//Left mouse button was released
	}
}

// Called by event polling when a KeyPressed event is found
void Game::keyPressed(const sf::Event::KeyPressed* event)
{
	// You can tell which button was pressed by the scancode to SFML's definitions of keyboard keys
	gs_manager.keyPressed(event);

}

// Called by event polling when a KeyReleased event is found
void Game::keyReleased(const sf::Event::KeyReleased* event)
{

	// Works the same way as KeyPressed
	gs_manager.keyReleased(event);

}
void Game::mouseMoved(const sf::Event::MouseMoved* event)
{
	gs_manager.mouseMoved(event);


	
	
}




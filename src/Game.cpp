
#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL)); //seeds random number generator with the current time
}

Game::~Game()
{
	

}

// We call this once after the game class is instantiated
bool Game::init()
{
	
	
	gs_manager.init();
	


  return true;
}

// Update runs after event polling and before rendering
// use it for everything that needs to update between frames
void Game::update(float dt)
{
	
	gs_manager.update(dt);
	
}
// for the queue i could make a square greyed out just bobbing up and down
// Runs after update, use it to tell the window what to draw this frame
void Game::render()
{
	gs_manager.render(window);
	
	

}



//Called by event polling when a MouseButtonPressed event is found
void Game::mouseButtonPressed(const sf::Event::MouseButtonPressed* event)
{
	// Event contains mouse position and which button was clicked

}


void Game::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
	gs_manager.handleEvent(event, window);
}
//Called by event polling when a MouseButtonReleased event is found
void Game::mouseButtonReleased(const sf::Event::MouseButtonReleased* event)
{
	gs_manager.mouseButtonReleased(event);
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




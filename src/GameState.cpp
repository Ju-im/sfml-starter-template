#include "GameState.h"

GameState::GameState() {

}
GameState::~GameState() {


}
bool GameState::init() {
	
	return true;
}
void GameState::update(float dt) {

	std::cout << "Currently in GameState update" << std::endl;
	

}
char GameState::exit()
{
	return 'n';
}


bool GameState::enter() {

	
	return true;

}
void GameState::render(sf::RenderWindow& window) {
	std::cout << "Currently in GameState render" << std::endl;
	

}

void GameState::mouseButtonPressed(const sf::Event::MouseButtonPressed* event) {

	sf::Vector2i position = event->position;
}

void GameState::mouseButtonReleased(const sf::Event::MouseButtonReleased* event) {
	sf::Vector2i position = event->position;
}


void GameState::keyPressed(const sf::Event::KeyPressed* event) {
	if (event->scancode == sf::Keyboard::Scancode::W)
	{
		// W was pressed
	}

}
void GameState::keyReleased(const sf::Event::KeyReleased* event) {

	// Works the same way as KeyPressed
	if (event->scancode == sf::Keyboard::Scancode::W)
	{
		// W was released
	}
}
void GameState::mouseMoved(const sf::Event::MouseMoved* event) {

	sf::Vector2i position = event->position;
}

void GameState::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
	//
}

bool GameState::clickCheck(sf::Vector2f mouse_pos, sf::FloatRect sprite) {

	return sprite.contains(mouse_pos);
}
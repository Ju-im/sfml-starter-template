#include "GameStateManager.h"
GameStateManager::GameStateManager() {


}


GameStateManager::~GameStateManager() {


}

bool GameStateManager::init() {
	current_state = play;
	
	current_state->init();
	return true;
}
void GameStateManager::mouseButtonPressed(const sf::Event::MouseButtonPressed* event) {

	current_state->mouseButtonPressed(event);
}

void GameStateManager::mouseButtonReleased(const sf::Event::MouseButtonReleased* event) {
	current_state->mouseButtonReleased(event);
}


void GameStateManager::keyPressed(const sf::Event::KeyPressed* event) {

	current_state->keyPressed(event);
}
void GameStateManager::keyReleased(const sf::Event::KeyReleased* event) {

	current_state->keyReleased(event);
}
void GameStateManager::mouseMoved(const sf::Event::MouseMoved* event) {

	current_state->mouseMoved(event);
}

void GameStateManager::switchState(GameState& newstate) {

	current_state;
}

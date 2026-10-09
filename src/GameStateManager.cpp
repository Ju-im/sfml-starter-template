#include "GameStateManager.h"
GameStateManager::GameStateManager() {


}


GameStateManager::~GameStateManager() {


}

bool GameStateManager::init() {
	current_state = menu;
	
	current_state->init();
	return true;
}
void GameStateManager::mouseButtonPressed(const sf::Event::MouseButtonPressed* event) {

	current_state->mouseButtonPressed(event);
}

void GameStateManager::update(float dt) {
	current_state->update(dt);
	char code = current_state->exit();
	
	if (code!='n') {
		std::cout << code << std::endl;
		switchState(static_cast<StateCode>(code));
			//Play,Pause,Menu,SaveMenu,Settings
			//P,E,M,S,T
	}
}

void GameStateManager::render(sf::RenderWindow& window) {

	current_state->render(window);
}

void GameStateManager::mouseButtonReleased(const sf::Event::MouseButtonReleased* event) {
	current_state->mouseButtonReleased(event);
}
void GameStateManager::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
	current_state->handleEvent(event, window);
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

void GameStateManager::switchState(StateCode code) {
	// Map the code to the appropriate GameState instance.
	
	/*if (static_cast<char>(current_code) == static_cast<char>(code)) {
		std::cout << "Same state" << std::endl;
		return;
	}*/
	switch (code) {
	case StateCode::Play:
		current_state = play;
		current_state->enter();

		break;
	case StateCode::Menu:
		current_state = menu;
		current_state->enter();
		break;
		// Add handling for other states as you implement them
	case StateCode::Pause:
		break;
	case StateCode::Save:
		current_state = save_menu;
		current_state->enter();
		break;
	case StateCode::Settings:
		break;
	}
}

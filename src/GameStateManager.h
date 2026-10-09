#pragma once
#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "Play.h"
#include "Menu.h"
#include "SaveMenu.h"
class GameStateManager
{
public:
	enum class StateCode : char {
		Play = 'P',
		Pause = 'E',
		Menu = 'M',
		Save = 'S',
		Settings = 'T'
	};
	GameStateManager();
	~GameStateManager();
	StateCode current_code = StateCode::Menu;
	Play* play = new Play;
	Menu* menu = new Menu;
	SaveMenu* save_menu = new SaveMenu;
	GameState* current_state;
	bool init();
	void update(float dt);
	void render(sf::RenderWindow& window);
	void switchState(StateCode code);
	void mouseButtonPressed(const sf::Event::MouseButtonPressed* event);
	bool clickCheck(sf::Vector2f mouse_pos, sf::FloatRect sprite);
	void mouseButtonReleased(const sf::Event::MouseButtonReleased* event);
	void keyPressed(const sf::Event::KeyPressed* event);
	void keyReleased(const sf::Event::KeyReleased* event);
	void mouseMoved(const sf::Event::MouseMoved* event);

};

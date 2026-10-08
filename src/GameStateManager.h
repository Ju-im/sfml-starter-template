#pragma once
#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "Play.h"
class GameStateManager
{
public:
	GameStateManager();
	~GameStateManager();
	Play* play = new Play;
	GameState* current_state;
	bool init();
	void switchState(GameState& newstate);
	void mouseButtonPressed(const sf::Event::MouseButtonPressed* event);
	bool clickCheck(sf::Vector2f mouse_pos, sf::FloatRect sprite);
	void mouseButtonReleased(const sf::Event::MouseButtonReleased* event);
	void keyPressed(const sf::Event::KeyPressed* event);
	void keyReleased(const sf::Event::KeyReleased* event);
	void mouseMoved(const sf::Event::MouseMoved* event);

};

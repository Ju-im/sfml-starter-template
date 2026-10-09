#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
class GameState
{
public:
	enum class StateCode : char {
		Play = 'P',
		Pause = 'E',
		Menu = 'M',
		Save = 'S',
		Settings = 'T'
	};
	GameState();
	~GameState();
	virtual bool init();
	virtual void mouseButtonPressed(const sf::Event::MouseButtonPressed* event);
	virtual void mouseButtonReleased(const sf::Event::MouseButtonReleased* event);
	virtual void keyPressed(const sf::Event::KeyPressed* event);
	virtual void keyReleased(const sf::Event::KeyReleased* event);
	virtual void mouseMoved(const sf::Event::MouseMoved* event);
	virtual bool clickCheck(sf::Vector2f mouse_pos, sf::FloatRect sprite);
	virtual void handleEvent(const sf::Event& event, sf::RenderWindow& window);
	virtual void render(sf::RenderWindow& window);
	virtual void update(float dt);
	virtual char exit();
	virtual bool enter();
	sf::Vector2f window_size{ 1080,720 };
	
	

};

#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class GameState
{
public:
	GameState();
	~GameState();
	virtual bool init();
	virtual void mouseButtonPressed(const sf::Event::MouseButtonPressed* event);
	virtual void mouseButtonReleased(const sf::Event::MouseButtonReleased* event);
	virtual void keyPressed(const sf::Event::KeyPressed* event);
	virtual void keyReleased(const sf::Event::KeyReleased* event);
	virtual void mouseMoved(const sf::Event::MouseMoved* event);


	virtual void render(sf::RenderWindow& window);
	virtual void update(float dt);
};

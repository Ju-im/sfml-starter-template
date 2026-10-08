#pragma once
#include "GameState.h"
class Play:public GameState
{
public:
	Play();
	~Play();

	bool init() override;
	void mouseButtonPressed(const sf::Event::MouseButtonPressed* event) override;
	
	void mouseButtonReleased(const sf::Event::MouseButtonReleased* event) override;
	void keyPressed(const sf::Event::KeyPressed* event) override;
	void keyReleased(const sf::Event::KeyReleased* event) override;
	void mouseMoved(const sf::Event::MouseMoved* event) override;

	void render(sf::RenderWindow& window) override;
	void update(float dt) override;
	int count = 0;
};

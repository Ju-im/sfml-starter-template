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
	bool enter() override;
	int count = 0;

	sf::Texture backgroundTexture{ "../Data/Images/WhackaMole Worksheet/background.png" };
	sf::Texture reject_button_texture{ "../Data/Images/Critter Crossing/reject button.png" };
	sf::Texture reject{ "../Data/Images/Critter Crossing/reject.png" };
	sf::Sprite background{ backgroundTexture };
	sf::RectangleShape fade_rect;
	float fade_timer = 1.f;
	bool enter_check = false;
	bool hand = false;
};

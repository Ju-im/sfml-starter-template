#pragma once
#include "GameState.h"
#include "Passport.h"
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
	void handleEvent(const sf::Event& event, sf::RenderWindow& window)override;
	void render(sf::RenderWindow& window) override;
	void update(float dt) override;
	float easeOutBounce(float x);
	void dragSprite(sf::Sprite* sprite, sf::RenderWindow& window);
	bool enter() override;
	char exit() override;
	

	sf::Texture backgroundTexture{ "../Data/Images/WhackaMole Worksheet/background.png" };
	sf::Texture reject_button_texture{ "../Data/Images/Critter Crossing/reject button.png" };
	sf::Texture reject{ "../Data/Images/Critter Crossing/reject.png" };
	sf::Sprite background{ backgroundTexture };
	sf::RectangleShape fade_rect;
	sf::RectangleShape drop_rect{window_size};

	sf::RectangleShape view_area;
	sf::RectangleShape checking_room;
	sf::RectangleShape table;
	sf::RectangleShape util_section;

	sf::Sprite* dragged = nullptr;
	

	sf::Vector2f drag_offset;

	Passport passport;


	float fade_timer = 1.f;
	float drop_timer = 0.f;
	bool enter_check = false;
	bool exit_check = false;
	bool created_before = false;
	bool hand = false;
};

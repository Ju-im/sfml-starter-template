#pragma once
#include "GameState.h"
#include "Passport.h"
#include "Animal.h"
#include "Utility.h"
#include<vector>
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

	void setupStamp();
	void updateStamp(float dt);
	void updateAcceptStamp(float dt);
	void handleStampClick(sf::Vector2f mousePos);
	void handleAcceptStampClick(sf::Vector2f mousePos);
	void dragSprite(sf::Sprite* sprite, sf::RenderWindow& window);
	void newAnimal();
	std::vector<sf::Sprite> queue;
	sf::Texture* animals = new sf::Texture[3];

	int waves = 5;
	void nextWave(float dt);
	bool enter() override;
	char exit() override;
	

	sf::Texture backgroundTexture{ "../Data/Images/WhackaMole Worksheet/background.png" };
	sf::Texture reject_button_texture{ "../Data/Images/Critter Crossing/reject button.png" };
	sf::Texture reject{ "../Data/Images/Critter Crossing/reject.png" };

	sf::Texture accept_button_texture{ "../Data/Images/Critter Crossing/accept button.png" };
	sf::Texture accept{ "../Data/Images/Critter Crossing/accept.png" };

	sf::Sprite background{ backgroundTexture };
	sf::RectangleShape fade_rect;
	sf::RectangleShape drop_rect{window_size};

	sf::RectangleShape view_area;
	sf::RectangleShape checking_room;
	sf::Vector2f final_pos{ 100,270 };
	sf::RectangleShape table;
	sf::RectangleShape util_section;

	sf::RectangleShape stamp_holder_shadow;
	sf::RectangleShape stamp_holder;

	sf::RectangleShape accept_stamp_holder;
	sf::RectangleShape accept_stamp_shadow;
	sf::Sprite* dragged = nullptr;
	


	sf::CircleShape next_wave_circle;
	bool done = false;
	float flash_timer = 0.f;
	float flash_duration = 1.f;

	float timer = 0.f;
	float duration = 1.f;


	// Stamp animation
	sf::Vector2f stamp_start_pos;
	sf::Vector2f stamp_target_pos;
	sf::Vector2f stamp_home_pos;

	sf::Vector2f accept_home_pos;
	sf::Vector2f accept_target_pos;
	sf::Vector2f accept_start_pos;
	float y_offset = 50.f;

	float stamp_timer = 0.f;
	float stamp_duration = 0.45f;
	bool stamp_moving = false;
	bool stamp_returning = false;
	bool can_stamp = false;
	bool stamped = false;

	float accept_stamp_timer = 0.f;
	float accept_stamp_duration = 0.45f;
	bool accept_stamp_moving = false;
	bool accept_stamp_returning = false;
	bool accept_can_stamp = false;
	bool accept_stamped = false;
	sf::Vector2f accept_stamp_start_pos;
	// Mouse interaction
	bool hovering_stamp = false;

	sf::Vector2f drag_offset;

	//Passport passport;
	Animal* animal;
	const sf::Cursor cursor = sf::Cursor::createFromSystem(sf::Cursor::Type::Hand).value();
	const sf::Cursor arrow = sf::Cursor::createFromSystem(sf::Cursor::Type::Arrow).value();


	bool stamp_extended = false;
	bool accept_stamp_extended = false;
	float fade_timer = 1.f;
	float drop_timer = 0.f;



	bool enter_check = false;
	bool exit_check = false;
	bool created_before = false;
	bool hand = false;
};

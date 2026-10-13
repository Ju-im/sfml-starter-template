#pragma once
#include "Passport.h"
#include "Utility.h"
#include <cmath>
class Animal
{
public:
	Animal();
	~Animal();

	bool init(sf::RectangleShape& tab, sf::RectangleShape& view);
	sf::Sprite* getSprite();
	
	void takePassport(float dt);

	void givePassport(float dt);

	void render(sf::RenderWindow& window);
	void update(float dt);
	float easeOutBounce(float x);
	void walk_anim(float dt);
	void colorAnim(float dt);
	float easeInSine(float x);
	float easeOutBack(float x);
	void rejectWalk(float dt);
	void colorBlackAnim(float dt);

	sf::Vector2f final_pos;
	sf::Vector2f start_pos{ -300,400 };

	struct Result {
		sf::Sprite* sprite;
		sf::Vector2f offset;
		bool stamped = false;
		bool passed = false;
	};
	Result result;
	
	Passport* passport;
	bool being_dragged = false;
private:
	sf::Texture* animals = new sf::Texture[3];
	sf::Sprite* sprite;
	sf::Texture reject{ "../Data/Images/Critter Crossing/reject.png" };
	
	bool  finished = false;
	float walk_timer = 0.0f;
	float duration = 2.5f;

	bool  reject_walk_finished = false;
	float reject_walk_timer = 0.0f;
	float reject_walk_duration = 5.5f;

	sf::Color end_color;
	sf::Color start_color;

	

	float give_timer = 0.0f;
	float give_duration = 1.f;
	bool give_anim_finished = false;

	float take_timer = 0.0f;
	float take_duration = 3.f;
	bool take_anim_finished = false;
	
	float color_timer = 0.0f;
	float color_duration = 1.f;
	bool color_anim_finished = false;

	float color_black_timer = 0.0f;
	float color_black_duration = 3.f;
	bool color_black_anim_finished = false;
	const double pi = acos(-1.0);
	
	
};

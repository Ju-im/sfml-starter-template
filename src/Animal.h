#pragma once
#include "Passport.h"
#include <cmath>
class Animal
{
public:
	Animal();
	~Animal();

	bool init(sf::RectangleShape& tab, sf::RectangleShape& view);
	sf::Sprite* getSprite();
	
	void givePassport(float dt);

	void render(sf::RenderWindow& window);
	void update(float dt);
	float easeOutBounce(float x);
	void walk_anim(float dt);
	void colorAnim(float dt);
	float easeInSine(float x);
	float easeOutBack(float x);


	sf::Vector2f final_pos;
	sf::Vector2f start_pos{ -300,400 };
	Passport* passport;
private:
	sf::Texture* animals = new sf::Texture[3];
	sf::Sprite* sprite;
	bool  finished = false;
	float walk_timer = 0.0f;
	float duration = 3.0f;
	sf::Color end_color;
	sf::Color start_color;
	float give_timer = 0.0f;
	float give_duration = 1.f;
	bool give_anim_finished = false;

	float color_timer = 0.0f;
	float color_duration = 1.f;
	bool color_anim_finished = false;
	const double pi = acos(-1.0);
	
	
};

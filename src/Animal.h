#pragma once
#include "Passport.h"
class Animal
{
public:
	Animal();
	~Animal();

	bool init();
	sf::Sprite* getSprite();
	
	void render(sf::RenderWindow& window);
	void update(float dt);
	sf::Sprite* sprite;
	Passport* passport;
};

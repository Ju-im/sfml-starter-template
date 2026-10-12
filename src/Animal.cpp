#include "Animal.h"

Animal::Animal() {


}

Animal::~Animal() {

	

}

sf::Sprite* Animal::getSprite() {
	return sprite;
}

bool Animal::init(sf::RectangleShape& tab, sf::RectangleShape& view) {
	passport = new Passport();
	passport->init(tab, view);
	animals[0].loadFromFile("../Data/Images/Critter Crossing/elephant.png");
	animals[1].loadFromFile("../Data/Images/Critter Crossing/moose.png");
	animals[2].loadFromFile("../Data/Images/Critter Crossing/penguin.png");
	sprite = new sf::Sprite(animals[1]);
	
	return true;
}

void Animal::update(float dt) {

	passport->update(dt);
	if (!finished) {
		walk_anim(dt);
	}
}


void Animal::render(sf::RenderWindow& window) {
	
	window.draw(*sprite);

}
void Animal::givePassport() {

	float t = walk_timer / duration;
	t = std::clamp(t, 0.0f, 1.0f);

	float easedT = easeInSine(t);

	sf::Vector2f position = start_pos + (final_pos - start_pos) * easedT;

	sprite->setPosition(position);
}
void Animal::walk_anim(float dt) {
	

	if (walk_timer >= duration) {
		finished = true;
		return;
	}
	walk_timer += dt ;

	sprite->setPosition({ ( final_pos.x* easeOutBounce(walk_timer)),(final_pos.y * easeOutBounce(walk_timer)) });
	
	float t = walk_timer / duration;
	t = std::clamp(t, 0.0f, 1.0f);

	float easedT = easeOutBack(t);

	sf::Vector2f position = start_pos + (final_pos - start_pos) * easedT;
	
	sprite->setPosition(position);
	
	

}
float Animal::easeInSine(float x) {
  return 1 - cos((x * pi / 2));
}
float Animal::easeOutBack(float x) {

	double const c1 = 1.70158;
	double const c3 = c1 + 1;

	return 1 + c3 * pow(x - 1, 3) + c1 * pow(x - 1, 2);
}
float Animal::easeOutBounce(float x)
{
	const double n1 = 7.5625;
	const double d1 = 2.75;

	if (x < 1 / d1) {
		return n1 * x * x;
	}
	else if (x < 2 / d1) {
		return n1 * (x -= 1.5 / d1) * x + 0.75;
	}
	else if (x < 2.5 / d1) {
		return n1 * (x -= 2.25 / d1) * x + 0.9375;
	}
	else {
		return n1 * (x -= 2.625 / d1) * x + 0.984375;
	}
}
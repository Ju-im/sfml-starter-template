#include "Passport.h"

Passport::Passport() {


}

Passport::~Passport() {

	delete sprite;

}

bool Passport::init() {

	sprite = new sf::Sprite(texture);
	sprite->setScale({ 0.5,0.5 });
	return true;

}

void Passport::render(sf::RenderWindow& window) {

	window.draw(*sprite);
}

sf::Sprite* Passport::getSprite() {


	return sprite;
}
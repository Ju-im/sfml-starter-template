#include "Passport.h"

Passport::Passport() {


}

Passport::~Passport() {

	delete sprite;

}

bool Passport::init() {

	sprite = new sf::Sprite(texture);
	sprite->setScale({ 0.5,0.5 });
	animals[0].loadFromFile("../Data/Images/Critter Crossing/elephant.png");
	animals[1].loadFromFile("../Data/Images/Critter Crossing/moose.png");
	animals[2].loadFromFile("../Data/Images/Critter Crossing/penguin.png");
	sprite->setPosition({ 500.f,500.f });
	photo = new sf::Sprite(animals[0]);
	photo->setScale({ 0.3f,0.3f });
	photo->setPosition({ sprite->getPosition().x + (sprite->getGlobalBounds().size.x * 0.09f), sprite->getPosition().y + (sprite->getGlobalBounds().size.y * 0.65f) });
	return true;

}

void Passport::render(sf::RenderWindow& window) {

	window.draw(*sprite);
	window.draw(*photo);
}

sf::Sprite* Passport::getSprite() {


	return sprite;
}

void Passport::movePassport(sf::Vector2f newPos) {

	sprite->setPosition(newPos);
	photo->setPosition({ sprite->getPosition().x + (sprite->getGlobalBounds().size.x * 0.09f), sprite->getPosition().y + (sprite->getGlobalBounds().size.y * 0.65f) });
}
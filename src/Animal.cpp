#include "Animal.h"

Animal::Animal() {


}

Animal::~Animal() {

	

}

sf::Sprite* Animal::getSprite() {
	return sprite;
}

bool Animal::init() {
	passport = new Passport();



	return true;
}

void Animal::update(float dt) {

	passport->update(dt);
}

void Animal::render(sf::RenderWindow& window) {
	passport->render(window);

}
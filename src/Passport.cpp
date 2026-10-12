#include "Passport.h"


Passport::Passport() {


}

Passport::~Passport() {

	delete sprite;
	delete photo;

}



bool Passport::init(sf::RectangleShape& tab, sf::RectangleShape& view) {

	sprite = new sf::Sprite(texture);
	
	animals[0].loadFromFile("../Data/Images/Critter Crossing/elephant.png");
	animals[1].loadFromFile("../Data/Images/Critter Crossing/moose.png");
	animals[2].loadFromFile("../Data/Images/Critter Crossing/penguin.png");
	sprite->setPosition({ 500.f,500.f });
	photo = new sf::Sprite(animals[0]);
	photo->setScale({ 0.3f,0.3f });
	photo->setPosition({ sprite->getPosition().x + (sprite->getGlobalBounds().size.x * 0.09f), sprite->getPosition().y + (sprite->getGlobalBounds().size.y * 0.65f) });
	
	table.setPosition(tab.getPosition());
	table.setSize(tab.getSize());

	view_area.setPosition(view.getPosition());
	view_area.setSize(view.getSize());


	

	std::cout <<"Table Position: " << table.getPosition().y << std::endl;
	view_area = view;
	return true;

}

void Passport::update(float dt) {
	


	if (!view_area.getGlobalBounds().findIntersection(sprite->getGlobalBounds())) {
	
		sprite->setScale({ 0.3f,0.3f });
		photo->setScale({ 0.3f * 0.5f,0.3f * 0.5f });
		
	
	}
	else {

		sprite->setScale({ 0.5,0.5 });
		photo->setScale({ 0.3f,0.3f });
	}
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

void Passport::rotatePassport(float degrees) {

	sprite->setRotation(sf::degrees(degrees));
	photo->setRotation(sf::degrees(degrees));
}

void Passport::tableSize() {

	sprite->setScale({ sprite->getScale().x *0.3f ,sprite->getScale().y * 0.3f});
	photo->setScale({ photo->getScale().x* 0.3f,photo->getScale().y *0.3f });



}

void Passport::viewSize() {

	sprite->setScale({ sprite->getScale().x * 1.3f ,sprite->getScale().y * 1.3f });
	photo->setScale({ photo->getScale().x * 1.3f,photo->getScale().y * 1.3f });



}
#include "Play.h"


Play::Play() {

}

Play::~Play() {


}

bool Play::init() {

	std::cout << "Currently in Play init" << std::endl;
	return true;

}
void Play::update(float dt) {

	std::cout << "Currently in Play update" << std::endl;

}
void Play::render(sf::RenderWindow& window) {
	std::cout << "Currently in Play render" << std::endl;
	
}

void Play::mouseButtonPressed(const sf::Event::MouseButtonPressed* event) {

	sf::Vector2i position = event->position;
}

void Play::mouseButtonReleased(const sf::Event::MouseButtonReleased* event) {
	sf::Vector2i position = event->position;
}


void Play::keyPressed(const sf::Event::KeyPressed* event) {
	if (event->scancode == sf::Keyboard::Scancode::W)
	{
		count++;
	}
	std::cout << "Count :" << count << std::endl;

}
void Play::keyReleased(const sf::Event::KeyReleased* event) {

	// Works the same way as KeyPressed
	if (event->scancode == sf::Keyboard::Scancode::W)
	{
		// W was released
	}
}
void Play::mouseMoved(const sf::Event::MouseMoved* event) {

	sf::Vector2i position = event->position;
}
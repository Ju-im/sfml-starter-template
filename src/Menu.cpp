#include "Menu.h"


Menu::Menu() {

}

Menu::~Menu() {


}

bool Menu::init() {

	std::cout << "Currently in Menu init" << std::endl;
	return true;

}
void Menu::update(float dt) {

	std::cout << "Currently in Menu update" << std::endl;

}
void Menu::render(sf::RenderWindow& window) {
	std::cout << "Currently in Menu render" << std::endl;

}

void Menu::mouseButtonPressed(const sf::Event::MouseButtonPressed* event) {

	sf::Vector2i position = event->position;
}

void Menu::mouseButtonReleased(const sf::Event::MouseButtonReleased* event) {
	sf::Vector2i position = event->position;
}


void Menu::keyPressed(const sf::Event::KeyPressed* event) {
	if (event->scancode == sf::Keyboard::Scancode::W)
	{
		count--;
	}
	std::cout << "Count :" << count << std::endl;

}
void Menu::keyReleased(const sf::Event::KeyReleased* event) {

	// Works the same way as KeyPressed
	if (event->scancode == sf::Keyboard::Scancode::W)
	{
		// W was released
	}
}
void Menu::mouseMoved(const sf::Event::MouseMoved* event) {

	sf::Vector2i position = event->position;
}
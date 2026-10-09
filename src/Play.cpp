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

	//std::cout << "Currently in Play update" << std::endl;
	if (enter_check) {
		fade_timer -= dt;
		fade_rect.setFillColor(sf::Color(0, 0, 0, 255.f*fade_timer));
		fade_timer = std::clamp(fade_timer, 0.0f, 255.0f);
		if (fade_timer <= 0.f) {
			fade_rect.setFillColor(sf::Color(0, 0, 0, 255.f*fade_timer));
			enter_check = false;
		}
	}

}
void Play::render(sf::RenderWindow& window) {
	//std::cout << "Currently in Play render" << std::endl;
	window.draw(background);
	window.draw(fade_rect);
	if (hand) {
		const auto cursor = sf::Cursor::createFromSystem(sf::Cursor::Type::Hand).value();
		window.setMouseCursor(cursor);
	}
	else {
		const auto cursor = sf::Cursor::createFromSystem(sf::Cursor::Type::Arrow).value();
		window.setMouseCursor(cursor);

	}
	
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

bool Play::enter() {
	fade_rect.setSize({ 1080,720 });
	fade_rect.setFillColor(sf::Color::Black);
	
	enter_check = true;

	return true;
}
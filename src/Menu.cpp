#include "Menu.h"


Menu::Menu() {

}

Menu::~Menu() {


}

bool Menu::init() {
	
	fade_rect.setSize({ 1080,720 });
	fade_rect.setFillColor(sf::Color::Transparent);
	title_text.setString("Critters Crossing");
	
	title_text.setCharacterSize(50);

	title_text.setPosition({ window_size.x * 0.3f,window_size.y * 0.1f });

	start_text.setString("Start");
	start_text.setOrigin(start_text.getGlobalBounds().getCenter());
	float offset = start_text.getPosition().x - start_text.getGlobalBounds().getCenter().x;
	start_text.setPosition({ window_size.x * 0.5f + offset, window_size.y * 0.7f });
	start_text.setFillColor(sf::Color::White);
	start_text.setStyle(sf::Text::Underlined);

	return true;

}
void Menu::update(float dt) {

	//std::cout << "Currently in Menu update" << std::endl;
	if(start_option_clicked){
	
		bar_percent += dt*speed;
		fade_timer += dt * speed*10;
		bar_percent = std::clamp(bar_percent, 0.1f, 1.0f);
		rect.setSize({ rect.getSize().x, start_text.getGlobalBounds().size.y * bar_percent });
		if (bar_percent >= 0.9f && fade_timer>=230.f) {
			exit_check = true;
			fade_timer = 0.5f;
			bar_percent = 0.0f;
		}

		
		fade_rect.setFillColor(sf::Color(0, 0, 0, fade_timer));
		if (fade_timer >= 230.f) {
			fade_rect.setFillColor(sf::Color(0, 0, 0, 255));
			fade_timer = 1.f;
			exit_check = true;
		}

	}
	
	if (enter_check) {
		fade_timer -= dt;
		fade_rect.setFillColor(sf::Color(0, 0, 0, 255.f * fade_timer));
		fade_timer = std::clamp(fade_timer, 0.0f, 255.0f);
		if (fade_timer <= 0.f) {
			fade_rect.setFillColor(sf::Color(0, 0, 0, 255.f * fade_timer));
			enter_check = false;
		}
	}

}
char Menu::exit()
{
	
	if (exit_check) {
		exit_check = false;
		start_option_clicked = false;
		rect.setSize({ 0.f,0.f });
		fade_timer = 1.f;
		bar_percent = 0.0f;
		return static_cast<char>(StateCode::Save);
	}
	return 'n';
}

bool Menu::enter() {
	fade_timer = 1.f;
	bar_percent = 0.0f;
	start_option_clicked = false;
	rect.setSize({ 0.f,0.f });

	exit_check = false;
	enter_check = true;
	fade_rect.setSize({ 1080,720 });
	fade_rect.setFillColor(sf::Color::Black);

	enter_check = true;
	
	
	return true;
}
void Menu::render(sf::RenderWindow& window) {
	
	//window.draw(background);
	window.draw(title_text);
	window.draw(rect);
	window.draw(start_text);
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

void Menu::handleEvent(const sf::Event& event, sf::RenderWindow& window)
{

	if (const auto* mouse =
		event.getIf<sf::Event::MouseButtonPressed>())
	{
		if (mouse->button == sf::Mouse::Button::Left)
		{
			const sf::Vector2f mousePos =
				window.mapPixelToCoords(mouse->position);

			if (clickCheck(mousePos, start_text.getGlobalBounds()))
			{
				rect_anim(start_text);
			start_option_clicked = true;
			}
		}
	}

	if (const auto* mouse = event.getIf<sf::Event::MouseMoved>()) {

		sf::Vector2i position = mouse->position;

		sf::Vector2f mouse_posf = static_cast<sf::Vector2f>(position);
		mouse_posf = window.mapPixelToCoords(position);
		if (clickCheck(mouse_posf, start_text.getGlobalBounds())) {


			hand = true;

		}
		else {
			hand = false;
		}
	}
}

void Menu::rect_anim(sf::Text& text)
{
	sf::FloatRect bounds = text.getGlobalBounds();

	// Match the text's size
	rect.setSize(bounds.size);

	// Centre the rectangle around the text
	rect.setOrigin(rect.getSize() * 0.5f);

	// Match the text's centre position
	rect.setPosition(bounds.position + bounds.size * 0.5f);

	rect.setRotation(sf::degrees(180.f));
	rect.setFillColor(sf::Color::Red);

}

void Menu::mouseButtonPressed(const sf::Event::MouseButtonPressed* event) {

	sf::Vector2i position = event->position;
	
	sf::Vector2f mouse_posf = static_cast<sf::Vector2f>(position);
	
	
	if (event->button == sf::Mouse::Button::Left) {
		pos = position;
		

		left_clicked = true;
	}
	
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
	hover_mouse = position;
	

}




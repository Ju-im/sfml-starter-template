#include "SaveMenu.h"

SaveMenu::SaveMenu()
{
}

SaveMenu::~SaveMenu()
{
}

bool SaveMenu::init()
{
	return false;
}

void SaveMenu::mouseButtonPressed(const sf::Event::MouseButtonPressed* event)
{
	//
	sf::Vector2i position = event->position;

	sf::Vector2f mouse_posf = static_cast<sf::Vector2f>(position);


	if (event->button == sf::Mouse::Button::Left) {
		pos = position;


		left_clicked = true;
	}
}

void SaveMenu::mouseButtonReleased(const sf::Event::MouseButtonReleased* event)
{
	//
}

void SaveMenu::keyPressed(const sf::Event::KeyPressed* event)
{
	//
}

void SaveMenu::keyReleased(const sf::Event::KeyReleased* event)
{
	//
}

void SaveMenu::mouseMoved(const sf::Event::MouseMoved* event)
{
	//
	sf::Vector2i position = event->position;
	hover_mouse = position;
}

void SaveMenu::render(sf::RenderWindow& window)
{
	if (hand) {
		const auto cursor = sf::Cursor::createFromSystem(sf::Cursor::Type::Hand).value();
		window.setMouseCursor(cursor);
	}
	else {
		const auto cursor = sf::Cursor::createFromSystem(sf::Cursor::Type::Arrow).value();
		window.setMouseCursor(cursor);

	}

	if (left_clicked) {
		sf::Vector2i position = pos;

		sf::Vector2f mouse_posf = static_cast<sf::Vector2f>(position);
		mouse_posf = window.mapPixelToCoords(position);
		if (clickCheck(mouse_posf, back.getGlobalBounds())) {


			rect_anim(back);
			back_option_clicked = true;

			left_clicked = false;
		}
	}
	sf::Vector2i position = hover_mouse;

	sf::Vector2f mouse_posf = static_cast<sf::Vector2f>(position);
	mouse_posf = window.mapPixelToCoords(position);
	if (clickCheck(mouse_posf, back.getGlobalBounds())) {


		hand = true;

	}
	else {
		hand = false;
	}
	window.draw(rect);
	window.draw(back);
	window.draw(title);
	
	
	window.draw(fade_rect);
}



void SaveMenu::rect_anim(sf::Text& text)
{
	std::cout << "Rect anim in save menu" << std::endl;
	rect.setSize({ text.getGlobalBounds().size });
	rect.setOrigin(rect.getGlobalBounds().getCenter());
	rect.setRotation(sf::degrees(180));
	rect.setPosition({ text.getPosition() });
	rect.setFillColor(sf::Color::Red);

}


void SaveMenu::update(float dt)
{
	//
	if (enter_check) {
		fade_timer -= dt;
		fade_rect.setFillColor(sf::Color(0, 0, 0, 255.f * fade_timer));
		fade_timer = std::clamp(fade_timer, 0.0f, 255.0f);
		if (fade_timer <= 0.f) {
			fade_rect.setFillColor(sf::Color(0, 0, 0, 255.f * fade_timer));
			enter_check = false;
		}
	}

	if (back_option_clicked) {

		bar_percent += dt * speed;
		fade_timer += dt * speed * 10;
		bar_percent = std::clamp(bar_percent, 0.0f, 1.0f);
		std::cout << "Rect height: " << rect.getSize().y << std::endl;
		rect.setSize({ rect.getSize().x, back.getGlobalBounds().size.y * bar_percent });
		if (bar_percent >= 0.9f) {
			exit_check = true;
			
		}
	}
}

bool SaveMenu::enter()
{
	fade_timer = 1.f;
	bar_percent = 0.0f;
	back_option_clicked = false;

	back.setString("BACK");
	//back.setOrigin(back.getGlobalBounds().getCenter());
	float offset = back.getPosition().x - back.getGlobalBounds().getCenter().x;
	back.setPosition({ window_size.x * 0.5f + offset, window_size.y * 0.75f });
	back.setFillColor(sf::Color::White);
	back.setStyle(sf::Text::Underlined);



	fade_rect.setSize({ 1080,720 });
	fade_rect.setFillColor(sf::Color::Black);

	title.setString("Select save to contine or start a new game");

	title.setCharacterSize(20);

	title.setPosition({ window_size.x * 0.3f,window_size.y * 0.1f });

	rect.setSize({ 0.f,0.f });

	exit_check = false;
	enter_check = true;
	
	return true;


}

char SaveMenu::exit()
{

	if (exit_check) {
		exit_check = false;
		rect.setSize({ 0.f,0.f });
		fade_timer = 1.f;
		bar_percent = 0.0f;
		back_option_clicked = false;
		return static_cast<char>(StateCode::Menu);
	}
	return 'n';
}
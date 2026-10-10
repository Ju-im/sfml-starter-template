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

	window.draw(rect);
	window.draw(back);
	window.draw(title);
	window.draw(save_box);
	window.draw(save_text);

	window.draw(fade_rect);
}



void SaveMenu::rect_anim(sf::Text& text,sf::RectangleShape& rect)
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
		bar_percent = std::clamp(bar_percent, 0.1f, 1.0f);
		rect.setSize({ rect.getSize().x, back.getGlobalBounds().size.y * bar_percent });
		if (bar_percent >= 0.9f && fade_timer >= 230.f) {
			exit_check = true;
			fade_timer = .5f;
			bar_percent = 0.0f;
		}


		fade_rect.setFillColor(sf::Color(0, 0, 0, fade_timer));
		if (fade_timer >= 230.f) {
			fade_rect.setFillColor(sf::Color(0, 0, 0, 255));
			fade_timer = 1.f;
			exit_check = true;
		}

	}

	if (play_option_clicked) {
		
		bar_percent += dt * speed;
		fade_timer += dt * speed * 10;
		bar_percent = std::clamp(bar_percent, 0.1f, 1.0f);
		rect.setSize({ rect.getSize().x, save_text.getGlobalBounds().size.y * bar_percent });
		if (bar_percent >= 0.9f && fade_timer >= 230.f) {
			exit_check = true;
			fade_timer = .5f;
			bar_percent = 0.0f;
		}


		fade_rect.setFillColor(sf::Color(0, 0, 0, fade_timer));
		if (fade_timer >= 230.f) {
			fade_rect.setFillColor(sf::Color(0, 0, 0, 255));
			fade_timer = 1.f;
			exit_check = true;
		}

	}
}

void SaveMenu::handleEvent(
	const sf::Event& event,
	sf::RenderWindow& window)
{
	if (const auto* mouse =
		event.getIf<sf::Event::MouseButtonPressed>())
	{
		if (mouse->button == sf::Mouse::Button::Left)
		{
			const sf::Vector2f mousePos =
				window.mapPixelToCoords(mouse->position);

			if (clickCheck(mousePos, back.getGlobalBounds()))
			{
				rect_anim(back,rect);
				back_option_clicked = true;
			}

			if (clickCheck(mousePos, save_text.getGlobalBounds()))
			{
				rect_anim(save_text, rect);
				play_option_clicked = true;
			}
		}
	}

	if (const auto* mouse = event.getIf<sf::Event::MouseMoved>()) {

		sf::Vector2i position = mouse->position;

		sf::Vector2f mouse_posf = static_cast<sf::Vector2f>(position);
		mouse_posf = window.mapPixelToCoords(position);
		if (clickCheck(mouse_posf, back.getGlobalBounds())) {


			hand = true;

		}
		else if (clickCheck(mouse_posf, save_text.getGlobalBounds())) {


			hand = true;

		}
		else {
			hand = false;
		}
	}
}



bool SaveMenu::enter()
{
	fade_timer = 1.f;
	bar_percent = 0.0f;
	back_option_clicked = false;

	back.setString("BACK");
	
	float offset = back.getPosition().x - back.getGlobalBounds().getCenter().x;
	back.setPosition({ window_size.x * 0.5f + offset, window_size.y * 0.75f });
	back.setFillColor(sf::Color::White);
	back.setStyle(sf::Text::Underlined);

	save_text.setString("New");
	save_text.setPosition({ window_size.x * 0.2f , window_size.y * 0.2f });

	rect_anim(save_text, save_box);
	save_box.setScale({ 1.2f,1.2f });
	save_box.setFillColor(sf::Color::Transparent);
	save_box.setOutlineColor(sf::Color::White);
	save_box.setOutlineThickness(2.0f);

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

	if (exit_check && back_option_clicked) {
		exit_check = false;
		rect.setSize({ 0.f,0.f });
		fade_timer = 1.f;
		bar_percent = 0.0f;
		back_option_clicked = false;
		return static_cast<char>(StateCode::Menu);
	}
	else if (exit_check && play_option_clicked) {
		exit_check = false;
		rect.setSize({ 0.f,0.f });
		fade_timer = 1.f;
		bar_percent = 0.0f;
		play_option_clicked = false;
		return static_cast<char>(StateCode::Play);
	}
	return 'n';
}
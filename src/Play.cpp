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
	
		drop_timer += dt*0.5f;
		
		drop_rect.setPosition({ drop_rect.getPosition().x,((window_size.y) * easeOutBounce(drop_timer)) });
		//std::cout << "Easout: " << easeOutBounce(drop_timer)  << std::endl;
		if (drop_timer >= 1.f) {
			enter_check = false;
			drop_timer = 0.f;
		}
	}

}
float Play::easeOutBounce(float x)
{
	const double n1 = 7.5625;
	const double d1 = 2.75;

	if (x < 1 / d1) {
		return n1 * x * x;
	}
	else if (x < 2 / d1) {
		return n1 * (x -= 1.5 / d1) * x + 0.75;
	}
	else if (x < 2.5 / d1) {
		return n1 * (x -= 2.25 / d1) * x + 0.9375;
	}
	else {
		return n1 * (x -= 2.625 / d1) * x + 0.984375;
	}
}
void Play::render(sf::RenderWindow& window) {
	//std::cout << "Currently in Play render" << std::endl;
	window.draw(background);
	
	window.draw(view_area);
	window.draw(checking_room);
	passport.render(window);
	
	window.draw(drop_rect);
	
	
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
	if (event->button == sf::Mouse::Button::Left && dragged!=nullptr)
	{
		
		dragged = nullptr;
		//Left mouse button was released
	}
}


void Play::keyPressed(const sf::Event::KeyPressed* event) {
	if (event->scancode == sf::Keyboard::Scancode::W)
	{
		//
		exit_check = true;
	}
	

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

void Play::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
	//

		//Left mouse button was pressed


		
	
	

	if (const auto* mouse =
		event.getIf<sf::Event::MouseButtonPressed>())
	{
		if (mouse->button == sf::Mouse::Button::Left)
		{
			const sf::Vector2f mousePos =
				window.mapPixelToCoords(mouse->position);

			if (clickCheck(mousePos, passport
				.getSprite()->getGlobalBounds()))
			{
				drag_offset = mousePos - passport.getSprite()->getPosition();
				dragged = passport.getSprite();
			}

		}
	}
	dragSprite(dragged, window);

}
void Play::dragSprite(sf::Sprite* sprite , sf::RenderWindow& window) {




	if (sprite != nullptr) {

		sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
		
		const sf::Vector2f mousePos =
			window.mapPixelToCoords(mouse_pos);

		sf::Vector2f drag_pos = mousePos - drag_offset;
		sprite->setPosition({ drag_pos.x,drag_pos.y });
		passport.movePassport({ drag_pos.x,drag_pos.y });
	}

}
bool Play::enter() {
	fade_rect.setSize({ 1080,720 });
	fade_rect.setFillColor(sf::Color::Black);
	
	view_area.setSize({ window_size.x * 0.75f, window_size.y * 0.85f });
	view_area.setPosition({ window_size.x * 0.35f,window_size.y * 0.30f });
	view_area.setFillColor(sf::Color(24, 18, 18));

	drop_rect.setFillColor(sf::Color::Black);
	drop_rect.setPosition({ 0.f,0.f });
	background.setTexture(backgroundTexture);
	
	if (!created_before) {
		passport.init();
		
		created_before = true;

		checking_room.setSize({ window_size.x * 0.35f,window_size.y * 0.85f });
		checking_room.setPosition({ 0.f, window_size.y * 0.30f });
		checking_room.setFillColor(sf::Color(47, 38, 37));
	}
	fade_timer = 1.f;
	enter_check = true;
	exit_check = false;

	return true;
}

char Play::exit() {
	if (exit_check) {
		fade_timer = 1.f;
		enter_check = false;
		exit_check = false;
		return static_cast<char>(StateCode::Menu);
	}
	return 'n';
}
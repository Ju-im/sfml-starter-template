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
		return;
	}
	
	
	animal->update(dt);
	updateStamp(dt);


}

void Play::render(sf::RenderWindow& window) {
	//std::cout << "Currently in Play render" << std::endl;
	window.draw(background);
	
	
	if (enter_check) {
		window.draw(view_area);
		window.draw(checking_room);
		window.draw(table);
		window.draw(util_section);
		window.draw(drop_rect);
		return;
	}
	else {
		window.draw(view_area);
		window.draw(checking_room);
		animal->render(window);
		window.draw(table);
		window.draw(util_section);
		animal->passport->render(window);
		if (animal->result.stamped) {
			window.draw(*animal->result.sprite);
		}
		
		window.draw(reject_mark);
		window.draw(stamp_holder_shadow);
		window.draw(stamp_holder);
	}
	
	
	
	//passport.render(window);
	
	
	
	
	if (hand) {
		
		window.setMouseCursor(cursor);
	}
	else {
		
		window.setMouseCursor(arrow);

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
		animal->being_dragged = false;
		//Left mouse button was released
	}
}


void Play::keyPressed(const sf::Event::KeyPressed* event) {
	if (event->scancode == sf::Keyboard::Scancode::W)
	{
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


void Play::handleEvent(
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

			// Handle stamp interaction first.
			if (stamp_holder.getGlobalBounds().contains(mousePos))
			{
				
				handleStampClick(mousePos);
				return;
			}
			

			// Don't drag the passport while the stamp is moving.
			if (stamp_moving)
				return;

			if (clickCheck(
				mousePos,
				animal->passport->getSprite()->getGlobalBounds()))
			{
				// Only allow dragging if the stamp isn't covering
				// the passport for an active stamping action.
				
					drag_offset = mousePos -
						animal->passport->getSprite()->getPosition();

					dragged = animal->passport->getSprite();
				
				
			}
		}
	}

	// Handle stamp interaction first.
	if (const auto* mouse =
		event.getIf<sf::Event::MouseMoved>()) {
		const sf::Vector2f mousePos =
			window.mapPixelToCoords(mouse->position);
		if (stamp_holder.getGlobalBounds().contains(mousePos))
		{

			hand = true;
			
		}
		else {
			hand = false;
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
		animal->passport->movePassport({ drag_pos.x,drag_pos.y });
		animal->being_dragged = true;
	}

}
void Play::newAnimal()
{
	animal = new Animal();
	animal->init(table,view_area);
	final_pos.x = checking_room.getSize().x * 0.5f - animal->getSprite()->getGlobalBounds().size.x *0.5f;
	animal->final_pos = final_pos;
	//animal->getSprite()->setPosition(final_pos);
	animal->getSprite()->setPosition({ -300,500 });
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
		
		
		created_before = true;

		checking_room.setSize({ window_size.x * 0.35f,window_size.y * 0.85f });
		checking_room.setPosition({ 0.f, window_size.y * 0.30f });
		checking_room.setFillColor(sf::Color(47, 38, 37));

		table.setSize({ window_size.x * 0.35f,window_size.y * 0.25f });
		table.setPosition({ 0.f,window_size.y * 0.6f });
		table.setFillColor(sf::Color(133, 138, 110));

		util_section.setSize({ window_size.x * 0.35f,window_size.y * 0.25f });
		util_section.setPosition({ 0.f,window_size.y * 0.85f });
		util_section.setFillColor(sf::Color(60, 43, 30));
		
		setupStamp();
		//passport.init(table,view_area);
	}
	newAnimal();
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


void Play::setupStamp()
{
	stamp_holder.setTexture(&reject_button_texture);
	stamp_holder.setSize({ 400.f, 80.f });

	stamp_holder_shadow.setSize({ 400.f, 80.f });
	stamp_holder_shadow.setFillColor(
		sf::Color(0, 0, 0, 80)
	);

	// Original position on the desk.
	stamp_home_pos = { window_size.x*0.9f, 400.f };

	stamp_holder.setPosition(stamp_home_pos);

	// The shadow remains behind.
	stamp_holder_shadow.setPosition(
		stamp_home_pos + sf::Vector2f(0.f, y_offset)
	);

	// The visible imprint left on the passport.
	reject_mark.setTexture(&reject);
	reject_mark.setSize({ 45.f, 45.f });
	reject_mark.setFillColor(sf::Color::White);
	reject_mark.setPosition({ -100.f, -100.f });
}



void Play::updateStamp(float dt)
{
	if (!stamp_moving)
		return;

	stamp_timer += dt;

	float t = std::clamp(
		stamp_timer / stamp_duration,
		0.f,
		1.f
	);

	float easedT = easeOutBounce(t);

	sf::Vector2f position =
		stamp_start_pos +
		(stamp_target_pos - stamp_start_pos) * easedT;

	stamp_holder.setPosition(position);

	stamp_holder_shadow.setPosition({
		position.x,
		position.y + y_offset
		});

	if (t >= 1.f)
	{
		stamp_holder.setPosition(stamp_target_pos);

		stamp_moving = false;
		stamp_timer = 0.f;

		if (stamp_returning)
		{
			// The holder has finished returning home.
			stamp_returning = false;
			can_stamp = false;
			stamped = false;
			return;
		}

		// The holder has reached the passport.
		if (Utility::AABB(
			stamp_holder.getGlobalBounds(),
			animal->passport->getSprite()->getGlobalBounds()))
		{
			std::cout << "Stamping passport" << std::endl;

			animal->result.sprite->setTexture(reject);
			animal->result.sprite->setPosition(
				stamp_holder.getPosition()
			);

			animal->result.stamped = true;
			animal->result.passed = false;

			animal->result.offset =
				stamp_holder.getPosition() -
				animal->passport->getSprite()->getPosition();

			stamped = true;
		}
		else
		{
			std::cout << "Missed passport" << std::endl;

			stamped = false;
		}

		// Return home whether the stamp hit or missed.
		/*stamp_start_pos = stamp_holder.getPosition();
		stamp_target_pos = stamp_home_pos;

		stamp_timer = 0.f;
		stamp_moving = true;
		stamp_returning = true;*/
	}
}








void Play::handleStampClick(sf::Vector2f mousePos)
{
	if (stamp_moving)
		return;

	if (!stamp_holder.getGlobalBounds().contains(mousePos))
		return;

	stamp_start_pos = stamp_holder.getPosition();

	if (!stamp_extended)
	{
		// Extend the holder.
		stamp_target_pos = {
			stamp_home_pos.x - 300.f,
			stamp_home_pos.y
		};

		stamp_extended = true;
	}
	else
	{
		// Retract the holder.
		stamp_target_pos = stamp_home_pos;
		stamp_extended = false;
		can_stamp = false;
	}

	stamp_timer = 0.f;
	stamp_moving = true;
}

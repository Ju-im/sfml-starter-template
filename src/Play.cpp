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
	updateAcceptStamp(dt);
	nextWave(dt);
	bobQueue(dt);


}

void Play::render(sf::RenderWindow& window) {
	
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
		
		window.draw(next_wave_circle);
		window.draw(checking_room);
		animal->render(window);
		window.draw(view_area);
		window.draw(table);
		window.draw(util_section);
		animal->passport->render(window);
		for (auto& p : list_animals) {
			window.draw(*p.sprite);
		}

		if (animal->result.stamped) {
			window.draw(*animal->result.sprite);
		}

		window.draw(accept_stamp_shadow);
		window.draw(accept_stamp_holder);

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
		//exit_check = true;
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

void Play::bobQueue(float dt) {
	t = clock.getElapsedTime().asSeconds();

	
	for (int i = 0; i<list_animals.size();i++) {
		float s = std::sin(5 * t + i);

		list_animals[i].sprite->move({0.f,s*0.5f});
	}

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

		if (mouse->button == sf::Mouse::Button::Left)
		{
			const sf::Vector2f mousePos =
				window.mapPixelToCoords(mouse->position);

			if (next_wave_circle.getGlobalBounds().contains(mousePos) && animal->done ) {
				done = true;
			}



			// Handle stamp interaction first.
			if (accept_stamp_holder.getGlobalBounds().contains(mousePos))
			{

				handleAcceptStampClick(mousePos);
				return;
			}


			// Don't drag the passport while the stamp is moving.
			if (accept_stamp_moving)
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
		

		else if (accept_stamp_holder.getGlobalBounds().contains(mousePos))
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
	animal->accept_start_pos = final_pos;
	animal->accept_final_pos = final_pos + sf::Vector2f(400.f, 50.f);
	animal->getSprite()->setPosition({ -300,500 });
	done = false;
	animal->done = false;
}
void Play::nextWave(float dt)
{
	if (animal->done && !done) {
		
		if (flash_timer >= flash_duration) {
			timer += dt;
			next_wave_circle.setFillColor(sf::Color::White);
			if (timer >= duration) {
				flash_timer = 0.f;
				timer = 0.f;
			}
		}
		else {
			flash_timer += dt;
			next_wave_circle.setFillColor(sf::Color(141, 141, 141));


		}


	}
	
	
	
	if (animal->done && done) {
		next_wave_circle.setFillColor(sf::Color(141, 141, 141));
		if (moveLine(list_animals.front(), dt)) {
			newAnimal();
		}
		
		
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

	animals[0].loadFromFile("../Data/Images/Critter Crossing/elephant.png");
	animals[1].loadFromFile("../Data/Images/Critter Crossing/moose.png");
	animals[2].loadFromFile("../Data/Images/Critter Crossing/penguin.png");
	
	
	if (!created_before) {
		
		
		created_before = true;
		for (int i = 0; i < waves; i++) {
			
			/*sf::Sprite critter(animals[2]);
			critter.setPosition({ i * critter.getGlobalBounds().size.x * 0.5f, 0.f });
			critter.setColor(sf::Color(10, 10, 10));
			critter.setScale({ 0.5f,0.5f });
			queue.push_back(critter);*/
			queue_animal a = q;
			a.sprite = new sf::Sprite(animals[2]);
			a.sprite->setColor(sf::Color(10, 10, 10));
			a.sprite->setScale({ 0.5f,0.5f });
			a.sprite->setPosition({ i * a.sprite->getGlobalBounds().size.x * 0.5f, 0.f });
			a.off_screen = false;
			list_animals.push_back(a);
			
		}
		std::cout << list_animals.size();
		checking_room.setSize({ window_size.x * 0.35f,window_size.y * 0.85f });
		checking_room.setPosition({ 0.f, window_size.y * 0.30f });
		checking_room.setFillColor(sf::Color(47, 38, 37));

		table.setSize({ window_size.x * 0.35f,window_size.y * 0.25f });
		table.setPosition({ 0.f,window_size.y * 0.6f });
		table.setFillColor(sf::Color(133, 138, 110));

		util_section.setSize({ window_size.x * 0.35f,window_size.y * 0.25f });
		util_section.setPosition({ 0.f,window_size.y * 0.85f });
		util_section.setFillColor(sf::Color(60, 43, 30));
		

		

		next_wave_circle.setFillColor(sf::Color(141, 141, 141));
		next_wave_circle.setRadius(50.f);
		next_wave_circle.setPosition({ window_size.x * 0.8f,window_size.y * 0.10f });
		



		setupStamp();
		
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

	accept_stamp_holder.setTexture(&accept_button_texture);
	accept_stamp_holder.setSize({ 400.f, 80.f });

	accept_stamp_shadow.setSize({ 400.f, 80.f });
	accept_stamp_shadow.setFillColor(
		sf::Color(0, 0, 0, 80)
	);

	accept_home_pos = { window_size.x * 0.9f, 300.f };
	accept_stamp_holder.setPosition(accept_home_pos);

	accept_stamp_shadow.setPosition(accept_home_pos + sf::Vector2f(0.f, y_offset));

	

	stamp_holder.setTexture(&reject_button_texture);
	stamp_holder.setSize({ 400.f, 80.f });

	stamp_holder_shadow.setSize({ 400.f, 80.f });
	stamp_holder_shadow.setFillColor(
		sf::Color(0, 0, 0, 80)
	);

	// Original position on the desk.
	stamp_home_pos = { window_size.x*0.9f, 600.f };

	stamp_holder.setPosition(stamp_home_pos);

	// The shadow remains behind.
	stamp_holder_shadow.setPosition(
		stamp_home_pos + sf::Vector2f(0.f, y_offset)
	);

	
	
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


void Play::updateAcceptStamp(float dt) {

	if (!accept_stamp_moving)
		return;

	accept_stamp_timer += dt;

	float t = std::clamp(
		accept_stamp_timer / stamp_duration,
		0.f,
		1.f
	);

	float easedT = easeOutBounce(t);

	sf::Vector2f position =
		accept_home_pos +
		(accept_target_pos  - accept_home_pos) * easedT;

	accept_stamp_holder.setPosition(position);

	accept_stamp_shadow.setPosition({
		position.x,
		position.y + y_offset
		});

	if (t >= 1.f)
	{
		accept_stamp_holder.setPosition(accept_target_pos);

		accept_stamp_moving = false;
		accept_stamp_timer = 0.f;

		if (accept_stamp_returning)
		{
			// The holder has finished returning home.
			accept_stamp_returning = false;
			accept_can_stamp = false;
			accept_stamped = false;
			return;
		}

		// The holder has reached the passport.
		if (Utility::AABB(
			accept_stamp_holder.getGlobalBounds(),
			animal->passport->getSprite()->getGlobalBounds()))
		{
			std::cout << "Stamping passport" << std::endl;
			if (!animal->result.stamped) {
				animal->result.sprite->setTexture(accept);
				animal->result.sprite->setPosition(
					accept_stamp_holder.getPosition()
				);

				animal->result.stamped = true;
				animal->result.passed = true;



				animal->result.offset =
					accept_stamp_holder.getPosition() -
					animal->passport->getSprite()->getPosition();

				accept_stamped = true;
			}
			else {
				//

			}
			
		}
		else
		{
			std::cout << "Missed passport" << std::endl;

			accept_stamped = false;
		}

		
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


void Play::handleAcceptStampClick(sf::Vector2f mousePos)
{
	if (accept_stamp_moving)
		return;

	if (!accept_stamp_holder.getGlobalBounds().contains(mousePos))
		return;

	accept_stamp_start_pos = stamp_holder.getPosition();

	if (!accept_stamp_extended)
	{
		// Extend the holder.
		accept_target_pos = {
			accept_home_pos.x - 300.f,
			accept_home_pos.y
		};

		accept_stamp_extended = true;
	}
	else
	{
		// Retract the holder.
		accept_target_pos = accept_home_pos;
		accept_stamp_extended = false;
		accept_can_stamp = false;
	}

	accept_stamp_timer = 0.f;
	accept_stamp_moving = true;
}


void Play::moveAnimalLine(sf::Sprite& sprite, float dt) {

	sprite.move({ -10.f * dt,0.f });
	bool r = offScreenX(sprite.getGlobalBounds());

	//auto const new_end = std::remove_if(queue.begin(), queue.end(), sprite.);
	//queue.erase(new_end, queue.end());
	
}
bool Play::moveLine(queue_animal& ani, float dt)
{
	if (list_animals.size() == 0) {
		return false;
	}
	ani.sprite->move({ -20.f * dt,0.f });
	bool r = offScreenXList(ani);

	auto new_end = std::remove_if(list_animals.begin(), list_animals.end(), [](const queue_animal& l) { return l.off_screen; });
	list_animals.erase(new_end, list_animals.end());
	std::cout << "New size is: " << list_animals.size() << std::endl;
	std::cout << r << std::endl;
	return r;

}
bool Play::offScreenXList(queue_animal& animal_in_queue)
{
	
		if (animal_in_queue.sprite->getGlobalBounds().position.x + animal_in_queue.sprite->getGlobalBounds().size.x < 0.f) {
			animal_in_queue.off_screen = true;
			return true;
		}
		else {
			animal_in_queue.off_screen = false;
			return false;
		}
	
}
bool Play::offScreenX(sf::FloatRect box) {
	

	if (box.position.x + box.size.x <= 0.f) {
		
		return true;
	}
	else { return false; }
	
}


#include "Animal.h"

Animal::Animal() {


}

Animal::~Animal() {

	

}

sf::Sprite* Animal::getSprite() {
	return sprite;
}



bool Animal::init(sf::RectangleShape& tab, sf::RectangleShape& view) {
	passport = new Passport();
	passport->init(tab, view);
	passport->getSprite()->setPosition(start_pos);
	animals[0].loadFromFile("../Data/Images/Critter Crossing/elephant.png");
	animals[1].loadFromFile("../Data/Images/Critter Crossing/moose.png");
	animals[2].loadFromFile("../Data/Images/Critter Crossing/penguin.png");
	sprite = new sf::Sprite(animals[1]);
	end_color = sprite->getColor();
	sprite->setColor(sf::Color::Black);
	start_color = sprite->getColor();
	result.sprite  = new sf::Sprite(reject);
	result.sprite->setScale({ 1.5f,1.5f });
	return true;
}
void Animal::update(float dt) {

	passport->update(dt);
	result.sprite->setScale(passport->getSprite()->getScale());
	if (!finished) {
		walk_anim(dt);
	}
	
	if (result.stamped && !reject_walk_finished&&!being_dragged && !result.passed) {
		if (passport->getSprite()->getGlobalBounds().findIntersection(sprite->getGlobalBounds())) {
			takePassport(dt);
		}
		
		colorBlackAnim(dt);
		rejectWalk(dt);
		//std::cout << " result x: " << result.sprite->getPosition().x << "result y: " << result.sprite->getPosition().y << std::endl;
		
		
	}

	if (result.stamped && !accept_walk_finished && !being_dragged && result.passed) {
		if (passport->getSprite()->getGlobalBounds().findIntersection(sprite->getGlobalBounds())) {
			takePassport(dt);
		}
		colorBlackAnim(dt);
		acceptWalk(dt);
	}
	sf::Vector2f diff = passport->getSprite()->getPosition();
	sf::Vector2f drag_pos = (diff + result.offset);
	result.sprite->setPosition({ drag_pos.x,drag_pos.y });

}



void Animal::render(sf::RenderWindow& window) {
	
	window.draw(*sprite);
	

}
void Animal::takePassport(float dt) {
	
	
	if (take_anim_finished && !result.passed) {
		
		colorBlackAnim(dt);
		return;
	}
	
	if (take_timer >= take_duration) {
		take_anim_finished = true;
		finished = true;
		passport->getSprite()->setColor(sf::Color::Transparent);
		passport->photo->setColor(sf::Color::Transparent);
		result.sprite->setColor(sf::Color::Transparent);

		return;
	}
	passport->getSprite()->setColor(sf::Color::White);
	passport->photo->setColor(sf::Color::White);
	take_timer += dt;

	float t = take_timer / take_duration;

	t = std::clamp(t, 0.0f, 1.0f);

	float easedT = easeInSine(t);
	sf::Vector2f e = { sprite->getPosition().x,sprite->getPosition().y - 20.f };
	sf::Vector2f position = getSprite()->getPosition() + (e - getSprite()->getPosition()) * easedT;

	passport->movePassport(position);

}



void Animal::givePassport(float dt) {

	if (give_timer >= give_duration) {
		give_anim_finished = true;
		
		return;
	}
	passport->getSprite()->setColor(sf::Color::White);
	passport->photo->setColor(sf::Color::White);
	give_timer += dt;
	float t = give_timer / give_duration;
	t = std::clamp(t, 0.0f, 1.0f);
	
	float easedT = easeInSine(t);
	sf::Vector2f e = { sprite->getPosition().x,sprite->getPosition().y + 100.f };
	sf::Vector2f position = getSprite()->getPosition() + (e - getSprite()->getPosition()) * easedT;

	passport->movePassport(position);
	
	//passport->rotatePassport(45.f);
}
void Animal::walk_anim(float dt) {
	

	if (walk_timer >= duration) {
		
		colorAnim(dt);
		return;
	}
	walk_timer += dt ;


	
	float t = walk_timer / duration;
	t = std::clamp(t, 0.0f, 1.0f);

	float easedT = easeOutBack(t);

	sf::Vector2f position = start_pos + (final_pos - start_pos) * easedT;
	
	sprite->setPosition(position);


}


void Animal::rejectWalk(float dt) {
	if (!color_black_anim_finished) {
		return;
	}
	if (reject_walk_finished) {
		std::cout << "Finished" << std::endl;
		return;
	}
	if (reject_walk_timer >= reject_walk_duration) {
		
		reject_walk_finished = true;
		done = true;
		return;
	}
	
	reject_walk_timer += dt;



	float t = reject_walk_timer / reject_walk_duration;
	t = std::clamp(t, 0.0f, 1.0f);

	float easedT = easeOutBack(t);

	sf::Vector2f position = final_pos + ((start_pos- sf::Vector2f{700.f,-700.f}) - final_pos)* easedT;

	sprite->setPosition(position);
}
void Animal::acceptWalk(float dt) {

	if (!color_black_anim_finished) {
		return;
	}
	if (accept_walk_finished) {
		std::cout << "Finished" << std::endl;
		return;
	}
	if (accept_walk_timer >= accept_walk_duration) {

		accept_walk_finished = true;
		done = true;
		return;
	}

	accept_walk_timer += dt;





	float t = accept_walk_timer / accept_walk_duration;
	t = std::clamp(t, 0.0f, 1.0f);

	float easedT = easeOutBack(t);

	sf::Vector2f position = accept_start_pos + (accept_final_pos - accept_start_pos) * easedT;

	sprite->setPosition(position);

}



void Animal::colorBlackAnim(float dt)
{
	if (!take_anim_finished) {
		return;
	}
	if (color_black_anim_finished) {
		
		return;
	}
	if (color_black_timer>= color_black_duration) {
		color_black_anim_finished = true;
		
		return;
	}
	color_black_timer += dt;
	float t = color_black_timer / color_black_duration;
	t = std::clamp(t, 0.0f, 1.0f);
	
	uint8_t red = end_color.r + (sf::Color::Black.r- end_color.r) * easeInSine(t);
	uint8_t green = end_color.g + (sf::Color::Black.g - end_color.g) * easeInSine(t);
	uint8_t blue = end_color.b + (sf::Color::Black.b- end_color.b) * easeInSine(t);
	sprite->setColor(sf::Color(red, green, blue));
}
void Animal::colorAnim(float dt) {
	if (color_timer >= color_duration) {
		color_anim_finished = true;
		givePassport(dt);
		return;
	}
	color_timer += dt;
	float t = color_timer / color_duration;
	t = std::clamp(t, 0.0f, 1.0f);
	uint8_t red = start_color.r + (end_color.r - start_color.r) * easeInSine(t);
	uint8_t green = start_color.g + (end_color.g - start_color.g) * easeInSine(t);
	uint8_t blue = start_color.b + (end_color.b - start_color.b) * easeInSine(t);
	sprite->setColor(sf::Color(red, green, blue));

}


float Animal::easeInSine(float x) {
  return 1 - cos((x * pi / 2));
}
float Animal::easeOutBack(float x) {

	double const c1 = 1.70158;
	double const c3 = c1 + 1;

	return 1 + c3 * pow(x - 1, 3) + c1 * pow(x - 1, 2);
}
float Animal::easeOutBounce(float x)
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


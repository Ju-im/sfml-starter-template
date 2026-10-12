#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class Passport
{
public:
	Passport();
	~Passport();

	bool init(sf::RectangleShape& tab, sf::RectangleShape& view);
	sf::Sprite* getSprite();
	void movePassport(sf::Vector2f newPos);
	void rotatePassport(float degrees);
	void tableSize();
	void viewSize();
	void render(sf::RenderWindow& window);
	void update(float dt);

private:
	sf::Texture texture{ "../Data/Images/Critter Crossing/default passport.png" };
	sf::Font font{ "../Data/Fonts/OpenSans-Bold.ttf" };
	sf::Font text_font{ "../Data/Fonts/open-sans/OpenSans-LightItalic.ttf" };
	sf::Texture* animals = new sf::Texture[3];
	sf::Sprite* photo;

	sf::Texture reject_button_texture{ "../Data/Images/Critter Crossing/reject button.png" };
	sf::Texture reject{ "../Data/Images/Critter Crossing/reject.png" };

	sf::RectangleShape table;
	sf::RectangleShape view_area;


	sf::Sprite reject_button{ reject_button_texture };
	sf::Sprite reject_stamp{ reject };

	sf::Text dob_title{ font };
	sf::Text gender_title{ font };
	sf::Text issue_title{ font };
	sf::Text exp_title{ font };
	sf::Sprite* sprite;


	int z_layer = 0;




};

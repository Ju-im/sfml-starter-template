#pragma once
#include <SFML/Graphics.hpp>
class Passport
{
public:
	Passport();
	~Passport();

	bool init();
	sf::Sprite* getSprite();
	void render(sf::RenderWindow& window);

private:
	sf::Texture texture{ "../Data/Images/Critter Crossing/default passport.png" };
	sf::Font font{ "../Data/Fonts/OpenSans-Bold.ttf" };
	sf::Font text_font{ "../Data/Fonts/open-sans/OpenSans-LightItalic.ttf" };

	sf::Text dob_title{ font };
	sf::Text gender_title{ font };
	sf::Text issue_title{ font };
	sf::Text exp_title{ font };
	sf::Sprite* sprite;
	int z_layer = 0;




};

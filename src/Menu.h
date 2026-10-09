#pragma once
#include "GameState.h"
class Menu :public GameState
{
public:
	Menu();
	~Menu();

	bool init() override;
	void mouseButtonPressed(const sf::Event::MouseButtonPressed* event) override;
	bool enter() override;
	void mouseButtonReleased(const sf::Event::MouseButtonReleased* event) override;
	void keyPressed(const sf::Event::KeyPressed* event) override;
	void keyReleased(const sf::Event::KeyReleased* event) override;
	void mouseMoved(const sf::Event::MouseMoved* event) override;
	void render(sf::RenderWindow& window) override;
	void handleEvent(const sf::Event& event, sf::RenderWindow& window) override;
	void rect_anim(sf::Text& text);
	void update(float dt) override;
	char exit() override;
	int count = 0;
	sf::Texture texture{ "../Data/Images/Critter Crossing/default passport.png" };
	sf::Font font{ "../Data/Fonts/OpenSans-Bold.ttf" };
	sf::Font text_font{ "../Data/Fonts/open-sans/OpenSans-LightItalic.ttf" };
	sf::RenderWindow tool;
	
	sf::Vector2i pos;
	sf::Texture backgroundTexture{ "../Data/Images/WhackaMole Worksheet/background.png" };
	sf::Sprite background{ backgroundTexture };
	sf::Text title_text{font};
	sf::Text start_text{ text_font };
	sf::Vector2f window_size{1080,720};
	bool hand = false;
	bool left_clicked = false;
	sf::Vector2i hover_mouse;

	sf::RectangleShape rect;
	float bar_percent = 0.0f;
	bool start_option_clicked = false;
	float speed = 20.0f;
	bool exit_check = false;
	sf::RectangleShape fade_rect;
	float fade_timer = 0.5f;

	bool enter_check = false;
	
};
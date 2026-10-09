#pragma once
#include "GameState.h"
class SaveMenu:public GameState
{
public:
	SaveMenu();
	~SaveMenu();
	bool init() override;
	void mouseButtonPressed(const sf::Event::MouseButtonPressed* event) override;
	void rect_anim(sf::Text & text);
	void mouseButtonReleased(const sf::Event::MouseButtonReleased* event) override;
	void keyPressed(const sf::Event::KeyPressed* event) override;
	void keyReleased(const sf::Event::KeyReleased* event) override;
	void mouseMoved(const sf::Event::MouseMoved* event) override;

	void render(sf::RenderWindow& window) override;
	void update(float dt) override;
	bool enter() override;
	char exit() override;

private:
	sf::Font font{ "../Data/Fonts/OpenSans-Bold.ttf" };
	sf::Font text_font{ "../Data/Fonts/open-sans/OpenSans-LightItalic.ttf" };

	sf::Text title{ font };
	sf::Text back{ text_font };
	sf::Text time{ text_font };
	sf::RectangleShape fade_rect;
	sf::RectangleShape rect;
	float fade_timer = 0.5f;
	bool enter_check = false;
	bool hand = false;
	float bar_percent = 0.0f;
	float speed = 10.0f;
	sf::Vector2i pos;
	bool left_clicked = false;
	bool back_option_clicked = false;
	sf::Vector2i hover_mouse;

	bool exit_check = false;
};

#ifndef SLIDER
#define SLIDER
#include "main.h"


class Slider {
private:
	sf::Texture texture;
	sf::Sprite background;
	int continuous;
	sf::Vector2f pos;
public:
	Slider()
	{
		texture.loadFromFile("Images/Ground.png");
		texture.setRepeated(1);
		background.setTexture(texture);
		background.setOrigin(0, 0);
		background.scale(1.5, 2);
		background.setTextureRect(sf::IntRect(0, 0, 1632, 26));
		background.setPosition(0, 574);
		continuous = 2;
		pos = sf::Vector2f(background.getPosition());
	}
	void draw(sf::RenderWindow* window) {
		window->draw(background);
	}
	void update(int t) {
		int ds = 4 + 4 * t / ACCEL;
		pos.x = pos.x - ds;

		if (pos.x < -816) {
			pos.x = 0;
		}
		background.setPosition(pos);
		pos = sf::Vector2f(background.getPosition());
	}
	~Slider() {}
};

#endif // !SLIDER


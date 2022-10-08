#ifndef ENTITY
#define ENTITY
#include "main.h"

class Entity {
private:
	sf::Vector2f pos;
	sf::Vector2f v;
	sf::Vector2f g;
	sf::Texture texture;
	sf::Sprite player;
	sf::IntRect rectangle;
	bool isJumping;
	bool onGround;
	bool getLow;
	int time;
	sf::FloatRect border;
	sf::Vector2f size;
public:
	Entity() : v(0, 0), g(0, 0.98), rectangle(0, 0, 50, 43) {
		isJumping = getLow = false;
		onGround = true;
		texture.loadFromFile("Images/dino.png");
		player.setPosition(50, 525);
		player.setTexture(texture);
		player.setTextureRect(rectangle);
		player.scale(1.5, 1.5);
		pos = sf::Vector2f(player.getPosition());
		time = 0;
		size = sf::Vector2f(20, 20);

	}

	void draw(sf::RenderWindow* window) {
		window->draw(player);
	}

	void keyboard_listen() {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && onGround) {
			v.y = -20;
			isJumping = true;
			onGround = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && onGround) {
			getLow = true;
			texture.loadFromFile("Images/down.png");
		}
		else {
			getLow = false;
		}
	}

	bool update(int frames) {
		pos += v;

		// Update of dino when Jumping
		if (!onGround) {
			v += g;
			if (pos.y >= 525) {
				pos.y = 525;
				onGround = true;
				isJumping = false;
				v.y = 0;
			}
		}
		if (!getLow) {
			texture.loadFromFile("Images/dino.png");
			rectangle = sf::IntRect(time, 0, 50, 43);
			time = (time != 0) ? 50 : 0;
			if (frames % 12 == 0)
				time = (time + 50) % 100;
			player.setTextureRect(rectangle);
			player.setPosition(pos);
			border = sf::FloatRect(this->pos, this->size);
		}
		else {
			rectangle = sf::IntRect(time, 0, 60, 43);
			time = (time != 0) ? 60 : 0;
			if (frames % 12 == 0)
				time = (time + 60) % 120;
			player.setTextureRect(rectangle);
			player.setPosition(pos);
			border = sf::FloatRect(sf::Vector2f(pos.x, 550), this->size);
		}


		if (onGround) {
			v = sf::Vector2f(0, 0);
		}

		return true;
	}

	sf::FloatRect& getRect() {
		return this->border;
	}
};

#endif // !ENTITY


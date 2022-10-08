#pragma once
#include "Entity.cpp"
#include "Slider.cpp"
#include "Obstacle.cpp"
#include "main.h"
#include <fstream>


class Score {
private:
	int prev_score;
	int s;
	sf::Text score;
	sf::Font font;
public:
	Score() {
		s = 0;
		font.loadFromFile("Font/SFPixelate.ttf");
	}
	void update(int high_score, int mTime) {
		std::string str = "Score: " + std::to_string(this->s) + "\nHigh Score: " + std::to_string(high_score);
		if (mTime)
			str += "\nMortal Time Left: " + std::to_string(mTime);
		this->score.setString(str);
		this->score.setFont(font);
		this->score.setCharacterSize(30);
		this->score.setPosition(sf::Vector2f(0, 0));
		this->score.setFillColor(sf::Color::Black);
	}
	void draw(sf::RenderWindow* window) {
		window->draw(score);
	}
	void add(int score) {
		prev_score = this->s;
		this->s += score;
	}
	int get_score() {
		return s;
	}
	int get_score_achieve() {
		int temp = s - prev_score;
		prev_score = s;
		return temp;
	}
	void reset() {
		s = 0;
	}
};

class Game {
private:
	sf::RenderWindow window;
	int frames;
	Entity player;
	Slider slider;
	std::vector<Obstacles*> obstacles;
	bool stop;
	int t;
	Score score;
	sf::Vector2f rightmost;
	//BACKGROUND
	sf::Texture texture;
	sf::Sprite background;
	int high_score = 0;
	bool mortal = false;
	int mTime;
	int mcount;
public:
	Game() : window(sf::VideoMode(WIDTH, HEIGHT), "Dragon Go") {
		window.setFramerateLimit(60);

		sf::Image img;
		img.loadFromFile("Images/icon.png");
		window.setIcon(img.getSize().x, img.getSize().y, img.getPixelsPtr());
		frames = 0;
		t = 0;
		mTime = 0;
		mcount = 0;
		stop = false;
		// seeding
		obstacles.push_back(new Cactus());
		rightmost = sf::Vector2f(866, 550);

		// Background
		texture.loadFromFile("Images/t-rex-game.png");
		background.setTexture(texture);
		background.scale(sf::Vector2f(.8, .8));

		// Read High Score
		std::ifstream in("Rec/record.txt");
		std::string str;
		getline(in, str);
		high_score = std::stoi(str);
		in.close();
	}

	void Run() {
		bool rendered = false;
		while (window.isOpen()) {
			sf::Event event;
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					window.close();
				}
				if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Escape)) {
					window.close();
				}
				if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::R)) {
					stop = false;
					rendered = false;
					window.clear();
					Restart();
				}
			}
			if (!stop) {
				Update();
				Render();
				t++;
			}
			else {
				if (!rendered) {
					sf::Text endgame;
					sf::Font font;
					font.loadFromFile("Font/SFPixelate.ttf");
					high_score = std::max(high_score, score.get_score());
					endgame.setString("You lose!!!");
					endgame.setFont(font);
					endgame.setCharacterSize(100);
					endgame.setPosition(sf::Vector2f(100, 200));
					endgame.setFillColor(sf::Color::Red);
					window.draw(endgame);
					window.display();

					// high_score
					std::ofstream out("Rec/record.txt");
					out << high_score;
					out.close();
					rendered = true;
				}
			}
			mTime = !mTime ? 0 : mTime - 1;
		}
	}

	void Update() {
		slider.update(t);
		// Ignore the collision by get bonus if there is no mortal bonus and no mortal time left
		if (!mTime)
			mortal = false;

		if (!mortal && !mTime)
			checkCollision();
		if (t % (SCORE * 10) == 0) {
			score.add(1);
		}

		int k = 0;
		if (obstacles.empty()) {
			obstacles.push_back(new Cactus());
		}

		if (obstacles.back()->getPos().x < WIDTH - MIN_DIST) {
			int r = rand() % 1000;
			if (r <= 500) {
				r = rand() % 10000;
				if (r <= 4000)
					obstacles.push_back(new Fly());
				else
					obstacles.push_back(new Cactus());

			}
		}
		for (auto enemy : obstacles) {
			enemy->update(frames, t);
			if (enemy->getPos().x < 0) {
				obstacles.erase(obstacles.begin());
				score.add(SCORE);
			}
		}
		//Create Bonus
		if (mcount <= 0 && !mortal) {
			obstacles.push_back(new Bonus());
			mcount = 500;
		}
		mcount -= score.get_score_achieve();

		player.keyboard_listen();
		score.update(high_score, mTime);
		player.update(frames);
		frames = ((frames + 1) % 60) + 1;
	}

	void Render() {

		window.clear(sf::Color(200, 200, 200));
		window.draw(background);
		slider.draw(&window);
		score.draw(&window);
		for (auto enimie : obstacles) {

			enimie->draw(&window);
		}

		player.draw(&window);

		window.display();
	}


	void checkCollision() {
		if (!obstacles.empty()) {
			for (auto iter = obstacles.begin(); iter != obstacles.end(); iter++) {
				if (player.getRect().intersects((*iter)->getRect())) {
					// Mortal 
					if ((*iter)->getID() == "BONUS") {
						mortal = true;
						mTime = MTIME;
						obstacles.erase(iter);
						break;
					}

					stop = true;
				}
			}
		}

	}

	void Restart() {
		t = 0;
		score.reset();
		obstacles.clear();

	}
	float length(const sf::Vector2f& v) {
		return std::sqrt(v.x * v.x + v.y * v.y);
	}

};



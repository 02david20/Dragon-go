#pragma once
#include "main.h"
class Obstacles
{
protected:
    sf::Texture texture;
    sf::Sprite enemies;
    sf::Vector2f position;
    bool enemy_on_screen;
    sf::FloatRect border;
    sf::Vector2f size;
public:
    Obstacles()
    {
        enemy_on_screen = true;
    }

    ~Obstacles()
    {
    }

    virtual void draw(sf::RenderWindow* window) = 0;

    virtual void update(int frames, int t) = 0;

    virtual sf::Vector2f getPos() = 0;

    virtual sf::FloatRect& getRect() = 0;

    virtual std::string getID() = 0;
};
class Cactus : public Obstacles {
private:
    std::string ID;
public:
    Cactus() : Obstacles() {
        this->ID = "CACTUS";
        this->enemy_on_screen = true;
        this->texture.loadFromFile("./Images/enemies.png");

        int k = rand() % 4;
        sf::IntRect rect;
        if (this->enemy_on_screen)
        {
            switch (k)
            {
            case 0:
                rect = sf::IntRect(0, 0, 50, 50);
                this->size = sf::Vector2f(50, 50);
                break;

            case 1:
                rect = sf::IntRect(50, 0, 50, 50);
                this->size = sf::Vector2f(25, 50);
                break;

            case 2:
                rect = sf::IntRect(0, 50, 50, 50);
                this->size = sf::Vector2f(30, 25);
                break;

            case 3:
                rect = sf::IntRect(50, 50, 50, 50);
                this->size = sf::Vector2f(25, 25);
                break;
            }
        }

        this->enemies.setTexture(texture);
        this->enemies.setTextureRect(rect);
        this->enemies.setPosition(866, 525);
        this->enemies.scale(sf::Vector2f(1.5, 1.5));
        srand(time(NULL));

        this->position = sf::Vector2f(enemies.getPosition());
    }
    void update(int frames, int t)
    {
        if (this->enemy_on_screen)
        {
            int ds = 4 + 4 * t / ACCEL;
            this->position.x = this->position.x - ds;
            enemies.setPosition(this->position);

            // set outline box
            this->border = sf::FloatRect(this->position, this->size);
        }
        this->position = sf::Vector2f(this->enemies.getPosition());
    }
    void draw(sf::RenderWindow* window)
    {
        window->draw(this->enemies);
    }

    sf::Vector2f getPos() {
        return this->enemies.getPosition();
    }
    sf::FloatRect& getRect() {
        return this->border;
    }
    std::string getID() {
        return this->ID;
    }
};
class Fly : public Obstacles {
private:
    std::string ID;
    int time;
    int y;
public:
    Fly() : Obstacles() {
        this->ID = "FLY";
        this->time = 0;
        sf::IntRect rect = sf::IntRect(0, 0, 50, 36);
        texture.loadFromFile("Images/Fly.png");
        this->size = sf::Vector2f(50, 50);
        this->enemies.setTexture(texture);
        this->enemies.setTextureRect(rect);
        int y = rand() % 100 + 450;
        this->enemies.setPosition(866, y);
        this->enemies.scale(sf::Vector2f(1.5, 1.5));
        this->position = sf::Vector2f(enemies.getPosition());
    }
    void update(int frames, int t)
    {
        texture.loadFromFile("Images/Fly.png");
        sf::IntRect rect = sf::IntRect(time, 0, 50, 36);
        if (frames % 12 == 0) {
            time = (time + 50) % 100;
        }
        this->enemies.setTexture(this->texture);
        this->enemies.setTextureRect(rect);
        if (this->enemy_on_screen)
        {
            int ds = 6 + 6 * t / ACCEL;
            this->position.x = this->position.x - ds;
            enemies.setPosition(this->position);
            //set outline box
            this->border = sf::FloatRect(this->position, this->size);
        }
        this->position = sf::Vector2f(this->enemies.getPosition());
    }
    void draw(sf::RenderWindow* window)
    {
        window->draw(this->enemies);
    }

    sf::Vector2f getPos() {
        return this->enemies.getPosition();
    }
    sf::FloatRect& getRect() {
        return this->border;
    }
    std::string getID() {
        return this->ID;
    }
};

class Bonus : public Obstacles {
private:
    std::string ID;
    int t = 0;
    int y;
    sf::IntRect rect;
public:
    Bonus() : Obstacles() {
        this->ID = "BONUS";
        rect = sf::IntRect(0, 0, 50, 50);
        texture.loadFromFile("Images/bonus.png");
        this->size = sf::Vector2f(20, 20);
        this->enemies.setTexture(texture);

        int y = rand() % 50 + 450;
        this->enemies.setPosition(866, y);
        this->enemies.scale(sf::Vector2f(1, 1));


        this->position = sf::Vector2f(enemies.getPosition());
    }
    void update(int frames, int t)
    {
        sf::IntRect rect = sf::IntRect(t, 0, 50, 50);

        /*  float ratio = frames % 12 / 12;*/
        this->enemies.setTexture(this->texture);
        this->enemies.setTextureRect(this->rect);

        if (this->enemy_on_screen)
        {
            int ds = 4 + 4 * t / ACCEL;
            this->position.x = this->position.x - ds;
            enemies.setPosition(this->position);

            this->border = sf::FloatRect(this->position, this->size);
        }
        this->position = sf::Vector2f(this->enemies.getPosition());
    }
    void draw(sf::RenderWindow* window)
    {
        window->draw(this->enemies);
    }

    sf::Vector2f getPos() {
        return this->enemies.getPosition();
    }
    sf::FloatRect& getRect() {
        return this->border;
    }
    std::string getID() {
        return this->ID;
    }
};
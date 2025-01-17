#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
using namespace sf;
using namespace std;

class Entity {
public:

    virtual void maj(float deltaTime) = 0;
    virtual void draw(RenderWindow & window) = 0;

};

class Player : public Entity {
private:

    CircleShape player;
    Vector2f position;
    Vector2f velocity;
    float speed;

public:

    Player() : position(100.f, 100.f), velocity(0.f, 0.f), speed(200) {
        player.setRadius(50.f);
        player.setFillColor(Color::White);
        player.setPosition(position);
    }

    void touche() {

        velocity = Vector2f(0.f, 0.f);

        if (Keyboard::isKeyPressed(Keyboard::Z)) {
            velocity.y -= speed;
        }
        if (Keyboard::isKeyPressed(Keyboard::S)) {
            velocity.y += speed;
        }
        if (Keyboard::isKeyPressed(Keyboard::Q)) {
            velocity.x -= speed;
        }
        if (Keyboard::isKeyPressed(Keyboard::D)) {
            velocity.x += speed;
        }
    }

    void maj(float deltaTime) override {
        position += velocity * deltaTime;
        player.setPosition(position);
    }

    void draw(RenderWindow& window) override {
        window.draw(player);
    }

};


int main() {

    RenderWindow window(VideoMode(1920, 1080), "Jeu d'aventure");
    window.setFramerateLimit(60);

    Player player;
    Clock clock;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::A)
                    cout << "La touche A a été pressée!" << endl;
                if (event.key.code == Keyboard::Escape)
                    window.close(); // Fermer avec Échap
            }
        }

        player.touche();
        float deltaTime = clock.restart().asSeconds();

        player.maj(deltaTime);


        window.clear();
        player.draw(window);
        window.display();
    }

    return 0;
}
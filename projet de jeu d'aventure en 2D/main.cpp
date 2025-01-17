#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <iostream>
#include <cmath>
using namespace sf;
using namespace std;

class Entity {
public:

    virtual void maj(float deltaTime, const Vector2u& windowSize) = 0;
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

    void maj(float deltaTime, const Vector2u& windowSize) override {

        position += velocity * deltaTime;

        float radius = player.getRadius();
        if (position.x < 0) position.x = 0;
        if (position.y < 0) position.y = 0;
        if (position.x + radius * 2 > windowSize.x) position.x = windowSize.x - radius * 2;
        if (position.y + radius * 2 > windowSize.y) position.y = windowSize.y - radius * 2;

        player.setPosition(position);

    }

    void draw(RenderWindow& window) override {
        window.draw(player);
    }

};

class Ennemi : public Entity {

protected :
    
    CircleShape ennemi;

public:

    Ennemi(float radius, Color color, Vector2f startPosition) {
        ennemi.setRadius(radius);
        ennemi.setFillColor(color);
        ennemi.setOrigin(radius, radius);
        ennemi.setPosition(startPosition);
    }

    FloatRect getBounds() const {

        return ennemi.getGlobalBounds();

    }

    void draw(RenderWindow& window) override {

        window.draw(ennemi);

    }
};

class patpatrouille : public Ennemi {

private:

    vector<Vector2f> waypoints;
    int actpos;
    float speed;

public:

    patpatrouille(Vector2f startPosition, vector<Vector2f> waypoints) : Ennemi(20.f, Color::Blue, startPosition), waypoints(waypoints), actpos(0), speed (80.f){}
    
    void maj(float deltaTime, const Vector2u& windowSize) override {

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
                    window.close(); 
            }
        }

        player.touche();
        float deltaTime = clock.restart().asSeconds();
        player.maj(deltaTime, window.getSize());
        window.clear();
        player.draw(window);
        window.display();
    }

    return 0;
}
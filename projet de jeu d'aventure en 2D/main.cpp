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
protected:

    CircleShape player;
    Vector2f velocity;
    float speed;

public:

    Vector2f position;

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

    FloatRect getBounds() const {
        return player.getGlobalBounds();
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
        if (waypoints.empty()) return;

        Vector2f target = waypoints[actpos];
        Vector2f direction = target - ennemi.getPosition();
        float lenght = sqrt(direction.x * direction.x + direction.y * direction.y);
        if (lenght != 0) {
            direction /= lenght;
        }
        ennemi.move(direction * speed * deltaTime);

        if (lenght < 5.f) {
            actpos = (actpos + 1) % waypoints.size();
        }
        
        Vector2f position = ennemi.getPosition();
        if (position.x - ennemi.getRadius() < 0) position.x = ennemi.getRadius();
        if (position.y - ennemi.getRadius() < 0) position.y = ennemi.getRadius();
        if (position.x + ennemi.getRadius() > windowSize.x) position.x = windowSize.x - ennemi.getRadius();
        if (position.y + ennemi.getRadius() > windowSize.y) position.y = windowSize.y - ennemi.getRadius();
        ennemi.setPosition(position);


    }

};

class HxH : public Ennemi {

private:

    float speed;

public:

    HxH(Vector2f startPosition) : Ennemi(20.f, Color::Red, startPosition), speed(100.f) {}

    void maj(float deltaTime, const Vector2f& playerposition, const Vector2u& windowSize) {
        
        Vector2f direction = playerposition - ennemi.getPosition();
        float lenght = sqrt(direction.x * direction.x + direction.y * direction.y);
        if (lenght != 0) {
            direction /= lenght;
        }

        ennemi.move(direction * speed * deltaTime);

        Vector2f position = ennemi.getPosition();
        if (position.x - ennemi.getRadius() < 0) position.x = ennemi.getRadius();
        if (position.y - ennemi.getRadius() < 0) position.y = ennemi.getRadius();
        if (position.x + ennemi.getRadius() > windowSize.x) position.x = windowSize.x - ennemi.getRadius();
        if (position.y + ennemi.getRadius() > windowSize.y) position.y = windowSize.y - ennemi.getRadius();
        ennemi.setPosition(position);

    }

    void maj(float deltaTime, const Vector2u& windowSize) override {}

};

bool checkCollision(const FloatRect& a, const FloatRect& b) {
    return a.intersects(b);
}

int main() {

    RenderWindow window(VideoMode(1920, 1080), "Jeu d'aventure");
    window.setFramerateLimit(60);

    Player player;
    Clock clock;

    vector<unique_ptr<Ennemi>> ennemis;
    ennemis.push_back(make_unique<HxH>(Vector2f(100.f, 100.f)));
    ennemis.push_back(make_unique<patpatrouille>(Vector2f(700.f, 500.f), vector<Vector2f>{ {700.f, 500.f}, { 700.f, 100.f }, { 100.f, 100.f }, { 100.f, 500.f }}));

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        float deltaTime = clock.restart().asSeconds();
        
        player.touche();
        player.maj(deltaTime, window.getSize());

        Vector2f playerPosition = player.getBounds().getPosition();

        for (auto& ennemi : ennemis) {
            if (HxH* chaser = dynamic_cast<HxH*>(ennemi.get())) {
                chaser->maj(deltaTime, player.position, window.getSize());
            }
            else
            {
                ennemi->maj(deltaTime, window.getSize());
            }
        }

        for (auto& ennemi : ennemis)
        {
            if (checkCollision(player.getBounds(), ennemi->getBounds())) {
                cout << "GAME OVER!!!!" << endl;
                return 0;
            }
        }

        window.clear();
        player.draw(window);
        for (auto& ennemi : ennemis) {
            ennemi->draw(window);
        }
        window.display();
    }

    
    return 0;
}
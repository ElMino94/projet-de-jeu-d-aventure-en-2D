#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
using namespace sf;
using namespace std;

class Entity {
public:

    virtual void update(float deltaTime) = 0;
    virtual void draw(sf::RenderWindow & window) = 0;

};

class Player : public Entity {
private:
    CircleShape shape;
    Vector2f position;
    Vector2f velocity;
public:
    

};





























int main() {
    RenderWindow window(VideoMode(1920, 1080), "Jeu d'aventure");

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

        window.clear();
        window.display();
    }

    return 0;
}
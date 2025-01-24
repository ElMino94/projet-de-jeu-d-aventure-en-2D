#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Player : public Entity {
protected:
    Sprite player;        
    Texture texture;      
    Vector2f velocity;
    float speed;
    float originalSpeed;
    float boostDuration;
    int clecollecter;

public:
    Vector2f position;

    Player();

    void loadTexture(const string& filename); 
    void touche();
    void maj(float deltaTime, const Vector2u& windowSize) override;
    void draw(RenderWindow& window) override;
    FloatRect getBounds() const;

    void increaseSpeed(float boostAmount, float duration = 5.f);
    void resetSpeed();

    void collectCle();
    int getCleCollecter() const;

    bool BoostOn() const;

    void setPosition(const Vector2f& newPosition) {
        position = newPosition;
        player.setPosition(position);
    }

    void wallCol(const vector<Sprite>& walls, const Vector2f& previousPostione);

};


#endif

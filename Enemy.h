#ifndef RPGGAME_ENEMY_H
#define RPGGAME_ENEMY_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class Enemy {
private:
    sf::RectangleShape sprite;
    int gold;
    int hp;
    int hpMax;
    int damage;
    float movementSpeed;
    float attackCooldown;
    void initVariables();
    void initSprite();
public:
    Enemy();
    virtual ~Enemy();
    void setPosition(float x, float y);
    void setHPDmg(int hpDmg);
    const int getHp() const;
    const sf::FloatRect getPos() const;
    void moveEn(float dirX, float dirY);
    void render(sf::RenderTarget& target);
};


#endif //RPGGAME_ENEMY_H

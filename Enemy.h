#ifndef RPGGAME_ENEMY_H
#define RPGGAME_ENEMY_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class Enemy {
private:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Vector2u spriteSize;
    int gold;
    int hp;
    int hpMax;
    int damage;
    float movementSpeed;
    float attackCooldown;
    void initVariables();
    void initSprite();
    void initShape();
public:
    Enemy();
    virtual ~Enemy();
    void setPosition(float x, float y);
    void setHPDmg(int hpDmg);
    const int getHp() const;
    const int getGold() const;
    float getMovementSpeed() const;
    const sf::FloatRect getPos() const;
    const sf::Vector2f& getLocalPos() const;
    void moveEn(float dirX, float dirY);
    void render(sf::RenderTarget& target);
};


#endif //RPGGAME_ENEMY_H

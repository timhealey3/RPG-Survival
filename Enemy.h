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
    sf::Clock animationClock;
    float animationSpeed = 0.13f;
    unsigned int currentFrame = 0;
    unsigned int frameCount = 5;
    int gold;
    int hp;
    int hpMax;
    int damage;
    float movementSpeed;
    float attackCooldown;
    float attackCooldownMax;
    void initVariables();
    void initSprite();
    void initShape();
public:
    Enemy();
    virtual ~Enemy();
    const bool canAttack();
    void setPosition(float x, float y);
    void setHPDmg(int hpDmg);
    int getHp() const;
    int getGold() const;
    float getMovementSpeed() const;
    sf::FloatRect getPos() const;
    const sf::Vector2f& getLocalPos() const;
    int getDmg() const;
    void moveEn(float dirX, float dirY);
    void render(sf::RenderTarget& target);

    void updateCooldown();

    void update();

    void setValues();

    void setValues(int level);
};


#endif //RPGGAME_ENEMY_H

#ifndef RPGGAME_PLAYER_H
#define RPGGAME_PLAYER_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "hitbox.h"
#include "Item.h"

class Player {
private:
    sf::Sprite sprite;
    sf::Texture texture;
    Item* item;
    sf::Vector2u spriteSize;
    sf::Clock animationClock;
    float animationSpeed = 0.11f;
    unsigned int currentFrame = 0;
    unsigned int frameCount = 6;
    int hp;
    int hpMax;
    int gold;
    bool isWalking;
    bool isAttacking;
    bool isLeft;
    bool isRight;
    bool isIdle;
    int damage;
    float attackCooldown;
    float attackCooldownMax;
    float movementSpeed;
    void initVariables();
    void initSprite();
public:
    Player();
    virtual ~Player();
    const bool canAttack();
    hitbox hitBox;
    const sf::FloatRect getBounds() const;
    const int getGold() const;
    const sf::Vector2f& getPos() const;
    void updateCooldown();
    int getDamage();
    void setPosition(float x, float y);
    void setAnimationFacing(int action);
    void addGold(int addGold);
    void subGold(int subGold);
    void setItem(const Item* newItem);
    Item *const getItem() const;
    void move(float dirX, float dirY);
    void render(sf::RenderTarget& target);
    void update();
};


#endif //RPGGAME_PLAYER_H

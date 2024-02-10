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
    sf::RectangleShape sprite;
    Item* item;
    int hp;
    int hpMax;
    int gold;
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
    void addGold(int addGold);
    void subGold(int subGold);
    void setItem(const Item* newItem);
    Item *const getItem() const;
    void move(float dirX, float dirY);
    void render(sf::RenderTarget& target);
    void update();
};


#endif //RPGGAME_PLAYER_H

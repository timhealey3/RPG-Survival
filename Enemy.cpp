//
// Created by Tim Healey on 1/27/24.
//

#include "Enemy.h"

Enemy::Enemy() {
    this->initVariables();
    this->initSprite();
    this->initShape();
}

Enemy::~Enemy() {

}

void Enemy::initVariables() {
    this->gold = 100;
    this->hpMax = 10;
    this->hp = hpMax;
    this->attackCooldown = 1.f;
    this->movementSpeed = 1.2;
}

void Enemy::initSprite() {
    this->texture.loadFromFile("/Users/timhealey/CLionProjects/rpgGame/Tileset/Skeleton/Idle.png");
    //spriteSize.x = 10;
    //spriteSize.y = 10;

    sprite.scale(.8f, .8f);
    sprite.setTextureRect(sf::IntRect(0, 0, spriteSize.x, spriteSize.y));

    sprite.setTexture(texture);
}


void Enemy::initShape() {
    this->sprite.setTexture(this->texture);
    this->sprite.scale(2.5f, 2.5f);
}


void Enemy::setPosition(const float x, const float y) {
    this->sprite.setPosition(x,y);
}

void Enemy::render(sf::RenderTarget &target) {
    target.draw(this->sprite);
}

void Enemy::moveEn(float dirX, float dirY) {
    this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}


const sf::FloatRect Enemy::getPos() const {
    return this->sprite.getGlobalBounds();
}

const int Enemy::getHp() const {
    return this->hp;
}

void Enemy::setHPDmg(int hpDmg) {
    this->hp -= hpDmg;
}

const int Enemy::getGold() const {
    return this->gold;
}

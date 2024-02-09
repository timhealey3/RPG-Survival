//
// Created by Tim Healey on 1/27/24.
//

#include "Enemy.h"

Enemy::Enemy() {
    this->initVariables();
    this->initSprite();
}

Enemy::~Enemy() {

}

void Enemy::initVariables() {
    this->gold = 5;
    this->hpMax = 10;
    this->hp = hpMax;
    this->attackCooldown = 1.f;
    this->movementSpeed = 1.2;
}

void Enemy::initSprite() {
    this->sprite.setSize(sf::Vector2f(100, 100));
    sprite.setFillColor(sf::Color::Red);
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

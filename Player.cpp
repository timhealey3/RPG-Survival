
#include "Player.h"

void Player::initVariables() {
    this->damage = 1;
    this->hpMax = 100;
    this->hp = this->hpMax;
    this->gold = 0;
    this->movementSpeed = 2.5f;
    this->attackCooldownMax = 10.f;
    this->attackCooldown = this->attackCooldownMax;
}

Player::Player() : hp(), hpMax(), gold(), movementSpeed() {
    this->initVariables();
    this->initSprite();
}

Player::~Player() {
}

void Player::move(const float dirX, const float dirY) {
    sf::Vector2f currentPosition = this->sprite.getPosition();
    this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}

void Player::initSprite() {
    this->sprite.setSize(sf::Vector2f(75, 75));
}

void Player::setPosition(const float x, const float y) {
    this->sprite.setPosition(x,y);
}

const sf::Vector2f &Player::getPos() const {
    return this->sprite.getPosition();
}

const bool Player::canAttack() {
    if (this->attackCooldown >= this->attackCooldownMax) {
        this->attackCooldown = 0.f;
        return true;
    }
    return false;
}

void Player::updateCooldown() {
    if (this->attackCooldown < this->attackCooldownMax) {
        this->attackCooldown += 0.5f;
    }
}

void Player::update() {
    this->updateCooldown();
}

void Player::render(sf::RenderTarget &target) {
    target.draw(this->sprite);
}

int Player::getDamage() {
    return this->damage;
}

const sf::FloatRect Player::getBounds() const {
    return this->sprite.getGlobalBounds();
}

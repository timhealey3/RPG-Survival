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
    this->damage = 10;
    this->hp = hpMax;
    this->attackCooldown = 1.f;
    this->movementSpeed = 0.8;
    this->attackCooldownMax = 15.f;
    this->attackCooldown = this->attackCooldownMax;
}

void Enemy::initSprite() {
    texture.loadFromFile("/Users/timhealey/CLionProjects/rpgGame/Tileset/char_purple_1.png");
    sprite.setTexture(texture);

    // Set the sprite size
    spriteSize.x = 56;
    spriteSize.y = 56;

    sprite.setTextureRect(sf::IntRect(0, 0, spriteSize.x, spriteSize.y));
    sprite.scale(2.5f, 2.5f);
    sprite.setOrigin(spriteSize.x / 2.f, spriteSize.y / 2.f);
}

void Enemy::initShape() {
    this->sprite.setTexture(this->texture);
}

void Enemy::setPosition(const float x, const float y) {
    this->sprite.setPosition(x,y);
}

void Enemy::render(sf::RenderTarget &target) {
    target.draw(this->sprite);
}

void Enemy::moveEn(float dirX, float dirY) {
    this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
    // if moving right
    if ((this->movementSpeed * dirX) >= 0) {
        if (animationClock.getElapsedTime().asSeconds() >= animationSpeed) {
            // Update the texture rect based on the current frame
            sprite.setTextureRect(
                    sf::IntRect(currentFrame * spriteSize.x, spriteSize.y * 2, spriteSize.x, spriteSize.y));
            sprite.setScale(2.5f, 2.5f);
            // Increment the current frame
            currentFrame++;
            // Wrap the animation loop
            if (currentFrame >= frameCount) {
                currentFrame = 0;
            }

            // Restart the animation clock
            animationClock.restart();
        }
    }
    // move left
    if ((this->movementSpeed * dirX) < 0) {
        if (animationClock.getElapsedTime().asSeconds() >= animationSpeed) {
            // Update the texture rect based on the current frame
            sprite.setTextureRect(
                    sf::IntRect(currentFrame * spriteSize.x, spriteSize.y * 2, spriteSize.x, spriteSize.y));
            sprite.setScale(-2.5f, 2.5f);
            // Increment the current frame
            currentFrame++;
            // Wrap the animation loop
            if (currentFrame >= frameCount) {
                currentFrame = 0;
            }
            // Restart the animation clock
            animationClock.restart();
        }
    }
}

sf::FloatRect Enemy::getPos() const {
    return this->sprite.getGlobalBounds();
}

int Enemy::getHp() const {
    return this->hp;
}

void Enemy::setHPDmg(int hpDmg) {
    this->hp -= hpDmg;
    sprite.setColor(sf::Color::Black);
}

int Enemy::getGold() const {
    return this->gold;
}

const sf::Vector2f &Enemy::getLocalPos() const {
    return this->sprite.getPosition();
}

float Enemy::getMovementSpeed() const {
    return this->movementSpeed;
}

int Enemy::getDmg() const {
    return this->damage;
}

const bool Enemy::canAttack() {
    if (this->attackCooldown >= this->attackCooldownMax) {
        this->attackCooldown = 0.f;
        return true;
    }
    return false;
}

void Enemy::updateCooldown()
{
    if (this->attackCooldown < this->attackCooldownMax) {
        this->attackCooldown += 0.5f;
    }
}

void Enemy::update()
{
    this->updateCooldown();
}



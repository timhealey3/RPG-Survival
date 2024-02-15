
#include "Player.h"

void Player::initVariables() {
    this->damage = 1;
    this->hpMax = 100;
    this->hp = this->hpMax;
    this->gold = 0;
    this->movementSpeed = 2.5f;
    this->attackCooldownMax = 15.f;
    this->isIdle = true;
    this->isRight = true;
    this->attackCooldown = this->attackCooldownMax;
}

Player::Player() : hp(), hpMax(), gold(), movementSpeed() {
    this->initVariables();
    this->initSprite();
    this->item = new Item("Wood Sword", 10, 25);
}

Player::~Player() {
    delete item;
}

void Player::move(const float dirX, const float dirY) {
    sf::Vector2f currentPosition = this->sprite.getPosition();
    this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}

void Player::initSprite() {
    texture.loadFromFile("/Users/timhealey/CLionProjects/rpgGame/Tileset/char1.png");
    sprite.setTexture(texture);

    // Set the sprite size
    spriteSize.x = 56;
    spriteSize.y = 56;

    sprite.setTextureRect(sf::IntRect(0, 0, spriteSize.x, spriteSize.y));
    sprite.scale(2.5f, 2.5f);
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
    // Increment the current frame
    sprite.setOrigin(spriteSize.x / 2.f, spriteSize.y / 2.f);

    if (this->isAttacking) {
        if (this->isRight) {
            if (animationClock.getElapsedTime().asSeconds() >= animationSpeed) {
                // Update the texture rect based on the current frame
                sprite.setTextureRect(sf::IntRect(currentFrame * spriteSize.x, spriteSize.y, spriteSize.x, spriteSize.y));
                sprite.setScale(2.5f, 2.5f);
                // Increment the current frame
                currentFrame++;
                // Wrap the animation loop
                if (currentFrame >= frameCount) {
                    currentFrame = 0;
                    this->isAttacking = false;
                }
                // Restart the animation clock
                animationClock.restart();
            }
        }
        if (this->isLeft) {
            if (animationClock.getElapsedTime().asSeconds() >= animationSpeed) {
                // Update the texture rect based on the current frame
                sprite.setTextureRect(sf::IntRect(currentFrame * spriteSize.x, spriteSize.y, spriteSize.x, spriteSize.y));
                sprite.setScale(-2.5f, 2.5f);
                // Increment the current frame
                currentFrame++;
                // Wrap the animation loop
                if (currentFrame >= frameCount) {
                    currentFrame = 0;
                    this->isAttacking = false;
                }
                // Restart the animation clock
                animationClock.restart();
            }
        }
    }
    if (this->isWalking) {
        if (this->isRight) {
            // Update animation only if enough time has passed
            if (animationClock.getElapsedTime().asSeconds() >= animationSpeed) {
                // Update the texture rect based on the current frame
                sprite.setTextureRect(sf::IntRect(currentFrame * spriteSize.x, spriteSize.y * 2, spriteSize.x, spriteSize.y));
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
        } else if (this->isLeft) {
            // Update animation only if enough time has passed
            if (animationClock.getElapsedTime().asSeconds() >= animationSpeed) {
                // Update the texture rect based on the current frame
                sprite.setTextureRect(sf::IntRect(currentFrame * spriteSize.x, spriteSize.y * 2, spriteSize.x, spriteSize.y));
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
    } else if (this->isIdle) {
        if (this->isRight) {
            // Update animation only if enough time has passed
            if (animationClock.getElapsedTime().asSeconds() >= animationSpeed) {
                // Update the texture rect based on the current frame
                sprite.setTextureRect(sf::IntRect(currentFrame * spriteSize.x, 0, spriteSize.x, spriteSize.y));
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
        } else if (this->isLeft) {
            // Update animation only if enough time has passed
            if (animationClock.getElapsedTime().asSeconds() >= animationSpeed) {
                // Update the texture rect based on the current frame
                sprite.setTextureRect(sf::IntRect(currentFrame * spriteSize.x, 0, spriteSize.x, spriteSize.y));
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

const int Player::getGold() const {
   return this->gold;
}

void Player::addGold(int addGold) {
    this->gold += addGold;
}

void Player::setItem(const Item* newItem) {
    delete this->item;
    this->item = new Item(newItem->getItemName(), newItem->getDamage(), newItem->getDurability());
}

Item *const Player::getItem() const {
    return this->item;
}

void Player::subGold(int subGold) {
    this->gold -= subGold;
}

void Player::setAnimationFacing(int action) {
    if (action == 0) {
        this->isIdle = true;
        this->isWalking = false;
    }
    if (action == 1) {
        this->isRight = false;
        this->isLeft = true;
        this->isIdle = false;
        this->isWalking = true;
    }
    if (action == 2) {
        this->isRight = true;
        this->isLeft = false;
        this->isIdle = false;
        this->isWalking = true;
    }
    if (action == 3) {
        this->isAttacking = true;
        this->isIdle = false;
    }
    if (action == 4) {
        this->isWalking = true;
        this->isIdle = false;
    }
}

const sf::FloatRect Player::getSwordBounds() const {
    float swordWidth = 18.0f;
    float swordHeight = 1.0f;

    sf::Vector2f swordPosition;

    if (this->isRight) {
        swordPosition = sf::Vector2f(this->getPos().x + 60.0f, this->getPos().y);
    } else {
        swordPosition = sf::Vector2f(this->getPos().x - 60.0f, this->getPos().y);
    }

    return sf::FloatRect(swordPosition.x, swordPosition.y, swordWidth, swordHeight);
}

void Player::brokeItem() {
    delete this->item;
    item = new Item("Wood Sword", 1, 25);
}



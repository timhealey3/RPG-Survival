
#include "Player.h"

void Player::initVariables() {
    this->damage = 1;
    this->hpMax = 100 ;
    this->hp = this->hpMax;
    this->gold = 0;
    this->attackCooldownMax = 15.f;
    this->attackCooldown = this->attackCooldownMax;
    this->isIdle = true;
    this->isRight = true;
    this->isAttacking = false;
    this->tileX = 1;
    this->tileY = 1;
}

Player::Player() : hp(), hpMax(), gold() {
    this->initVariables();
    this->initSprite();
    this->item = new Item("Wood Sword", 10, 25);
}

Player::~Player() {
    if (item) {
        delete item;
    }
}

void Player::move(const float dirX, const float dirY) {
    sf::Vector2f currentPosition = this->sprite.getPosition();
}

void Player::initSprite() {
    // Load the texture
    if (!texture.loadFromFile("/Users/timhealey/CLionProjects/rpgGame/Tileset/char1.png")) {
       std::cout << "ERROR::PLAYER::TEXTURE LOADING" << std::endl;
    }
    sprite.setTexture(texture);


    spriteSize.x = 56;
    spriteSize.y = 56;

    // Set the texture rect to use the first frame of 56x56 pixels
    sprite.setTextureRect(sf::IntRect(0, 0, spriteSize.x, spriteSize.y));

    this->scaleX = 32.0f / spriteSize.x;
    this->scaleY = 32.0f / spriteSize.y;

    sprite.setScale(scaleX, scaleY);

    sprite.setOrigin(spriteSize.x / 2.f, spriteSize.y / 2.f);
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
    this->updateAnimation();
}

void Player::updateAnimation(){
    if (this->isIdle) {
        if (animationClock.getElapsedTime().asSeconds() > animationSpeed) {
            // Update the texture rect based on the current frame
            sprite.setOrigin(spriteSize.x / 2.f, spriteSize.y / 2.f);
            if (this->isRight) {
                sprite.setScale(this->scaleX, this->scaleY);
            }
            if (this->isLeft) {
                sprite.setScale(-this->scaleX, this->scaleY);
            }
            sprite.setTextureRect(sf::IntRect(currentFrame * 56, 0, 56, 56));
            // Increment the current frame
            currentFrame++;
            // Wrap the animation loop
            if (currentFrame >= frameSword) {
                currentFrame = 0;
            }
            // Restart the animation clock
            animationClock.restart();
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

void Player::attackAnimation() {
    // Increment the current frames
    this->isAttacking = true;
    sprite.setOrigin(spriteSize.x / 2.f, spriteSize.y / 2.f);

    if (animationClock.getElapsedTime().asSeconds() > animationSpeed) {
        // Update the texture rect based on the current frame
        sprite.setTextureRect(sf::IntRect(currentFrame * 56, 56, 56, 56));
        // Increment the current frame
        currentFrame++;
        // Wrap the animation loop
        if (currentFrame >= frameSword) {
            std::cout << "two" << std::endl;
            currentFrame = 0;
            this->isAttacking = false;
        }
        // Restart the animation clock
        animationClock.restart();
    }
}

void Player::setItem(const Item* newItem) {
    delete this->item;
    this->item = new Item(newItem->getItemName(), newItem->getDamage(), newItem->getDurability());
}

Item *Player::getItem() const {
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
    if (action == 5) {
       this->isTakingDmg = true;
    }
}

sf::FloatRect Player::getSwordBounds() const {
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
    item = new Item("Fists", 1, 100);
}

int Player::getHp() const {
    return this->hp;
}

int Player::getHpMax() const {
    return this->hpMax;
}

void Player::setHp(int subHp) {
    if ((this->hp - subHp) <= 0) {
        this->hp = 0;
    }
    else {
        this->hp -= subHp;
    }
}

bool Player::getAttacking() {
    return this->isAttacking;
}

int Player::getTileX() {
    return tileX;
}

int Player::getTileY() {
    return tileY;
}

void Player::setTileX(int change) {
    tileX += change;
    sprite.setPosition(tileX * 32, tileY * 32);
}

void Player::setTileY(int change) {
    tileY += change;
    sprite.setPosition(tileX * 32, tileY * 32);
}

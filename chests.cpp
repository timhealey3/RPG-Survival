//
// Created by Tim Healey on 2/8/24.
//

#include "chests.h"

void Chest::initVariables() {
    this->tier = (std::rand() % 3) + 1;
    this->cost = tier * 100;
    this->opened = false;
}

Chest::Chest() {
    this->initVariables();
    this->initTexture();
    this->initShape();
    this->setPosition();
    this->setItem();
}

Chest::~Chest() {
    if (item) {
        delete item;
    }
}

void Chest::setPosition() {
    int x = std::rand() % 15;
    int y = std::rand() % 7;
    this->setTileX(x);
    this->setTileY(y);
}

void Chest::initShape() {
    this->shape.setTexture(this->texture);
}

void Chest::initTexture() {
   this->texture.loadFromFile("/Users/timhealey/CLionProjects/rpgGame/Tileset/Chests.png");
    sf::Vector2u spriteSize(32, 32);

    // Create a sprite to display a single frame
    shape.setTexture(texture);
    if (this->tier == 1)
        shape.setTextureRect(sf::IntRect(0, spriteSize.x * 0, spriteSize.x, spriteSize.y));
    else if (this->tier == 2)
        shape.setTextureRect(sf::IntRect(0, spriteSize.x * 2, spriteSize.x, spriteSize.y));
    else if (this->tier == 3)
        shape.setTextureRect(sf::IntRect(0, spriteSize.x * 4, spriteSize.x, spriteSize.y));

}

void Chest::render(sf::RenderTarget &target) {
    target.draw(this->shape);
}

const sf::Vector2f &Chest::getPos() const {
    return this->shape.getPosition();
}

const int Chest::getGold() const {
    return this->cost;
}

void Chest::setItem() {
    if (this->tier == 1) {
        item = new Item("Sword", 2, 25);
    }
    else if (this->tier == 2) {
        item = new Item("Gladius", 4, 15);
    }
    else if (this->tier == 3) {
        item = new Item("Sword of Neptune", 10, 60);
    }
    // should never hit
    else {
        item = new Item("Wood Sword", 1, 25);
    }
}

const Item* Chest::getItem() {
    return item;
}

void Chest::handleOpened() {
    this->opened = true;
    sf::Vector2u spriteSize(32, 32);
    if (this->tier == 1)
        shape.setTextureRect(sf::IntRect(0, spriteSize.x * 1, spriteSize.x, spriteSize.y));
    else if (this->tier == 2)
        shape.setTextureRect(sf::IntRect(0, spriteSize.x * 3, spriteSize.x, spriteSize.y));
    else if (this->tier == 3)
        shape.setTextureRect(sf::IntRect(0, spriteSize.x * 5, spriteSize.x, spriteSize.y));
}

bool Chest::getOpened() {
    if (!this->opened) {
        handleOpened();
        return false;
    }
    else
        return true;
}

int Chest::getTileX() {
    return tileX;
}

int Chest::getTileY() {
    return tileY;
}

void Chest::setTileY(int change) {
    tileX += change;
    shape.setPosition(tileX * 32, tileY * 32);
}

void Chest::setTileX(int change) {
    tileY += change;
    shape.setPosition(tileX * 32, tileY * 32);
}

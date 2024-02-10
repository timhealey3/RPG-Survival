//
// Created by Tim Healey on 2/8/24.
//

#include "chests.h"

void Chest::initVariables() {
    this->tier = (std::rand() % 3) + 1;
    this->cost = tier * 100;
}

Chest::Chest() {
    this->initVariables();
    this->initTexture();
    this->initShape();
    this->setPosition();
    this->setItem();
}

Chest::~Chest() {

}

void Chest::setPosition() {
    int x = std::rand() % 1000;
    int y = std::rand() % 1000;
    this->shape.setPosition(x,y);
}

void Chest::initShape() {
    this->shape.setTexture(this->texture);
    this->shape.scale(2.5f, 2.5f);
}

void Chest::initTexture() {
   this->texture.loadFromFile("/Users/timhealey/CLionProjects/rpgGame/Tileset/Chests.png");
    sf::Vector2u spriteSize(32, 32);

    // Create a sprite to display a single frame
    shape.setTexture(texture);
    shape.setTextureRect(sf::IntRect(0, 0, spriteSize.x, spriteSize.y));
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
        item = new Item("Sword", 2);
    }
    else if (this->tier == 2) {
        item = new Item("Gladius", 4);
    }
    else if (this->tier == 3) {
        item = new Item("Sword of Neptune", 10);
    }
    // should never hit
    else {
        item = new Item("Wood Sword", 1);
    }
}

const Item* Chest::getItem() const {
    return item;
}







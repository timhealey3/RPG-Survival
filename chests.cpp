//
// Created by Tim Healey on 2/8/24.
//

#include "chests.h"

void Chest::initVariables() {
    this->tier = std::rand() % 3;
    this->cost = tier * 100;
}

Chest::Chest() {
    this->initVariables();
    this->initTexture();
    this->initShape();
    this->setPosition();
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




//
// Created by Tim Healey on 2/8/24.
//

#ifndef RPGGAME_CHESTS_H
#define RPGGAME_CHESTS_H
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>

class Chest {
private:
    sf::Sprite shape;
    sf::Texture texture;
    int tier;
    int cost;
    // item
    void initVariables();
    void initShape();
    void initTexture();
public:
    Chest();
    virtual ~Chest();
    void render(sf::RenderTarget &target);
    const sf::Vector2f& getPos() const;
    const int getGold() const;
    void setPosition();
};


#endif //RPGGAME_CHESTS_H

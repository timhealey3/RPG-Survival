//
// Created by Tim Healey on 1/28/24.
//

#ifndef RPGGAME_TILES_H
#define RPGGAME_TILES_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "hitbox.h"

class TileMap : public sf::Drawable, public sf::Transformable {
private:
    sf::Texture tileset;
    sf::Texture m_tileset;
    const int* tiles;
    int tileX;
    int tileY;
    unsigned int height;
    unsigned int width;
    float scale;
    sf::Vector2u tileSize;
    sf::VertexArray m_vertices;
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
public:
    hitbox hitBox;
    bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);
    sf::Vector2u getTileSize() const;
    sf::FloatRect getTileBounds(unsigned int i, unsigned int j) const;

    bool isTileWalkable(float x, float y);
};


#endif //RPGGAME_TILES_H

//
// Created by Tim Healey on 1/28/24.
//

#ifndef RPGGAME_TILES_H
#define RPGGAME_TILES_H
#include <SFML/Graphics.hpp>

class TileMap : public sf::Drawable, public sf::Transformable {
private:
    sf::Texture tileset;
    sf::Texture m_tileset;
    const int* tiles;
    unsigned int height;
    unsigned int width;
    float scale;
    sf::Vector2u tileSize;
    sf::VertexArray m_vertices;
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
public:
    bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height, float scale);
};


#endif //RPGGAME_TILES_H

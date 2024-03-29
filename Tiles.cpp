#include "Tiles.h"

bool TileMap::load(const std::string &tileset, sf::Vector2u tileSize, const int *tiles, unsigned int width,
                   unsigned int height, float scale) {
    // load the tileset texture
    if (!m_tileset.loadFromFile(tileset))
        return false;

    // resize the vertex array to fit the Level size
    m_vertices.setPrimitiveType(sf::Triangles);
    m_vertices.resize(width * height * 6);

    // populate the vertex array, with two triangles per tile
    for (unsigned int i = 0; i < width; ++i)
        for (unsigned int j = 0; j < height; ++j)
        {
            // get the current tile number
            int tileNumber = tiles[i + j * width];

            // find its position in the tileset texture
            int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
            int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

            // get a pointer to the triangles' vertices of the current tile
            sf::Vertex* triangles = &m_vertices[(i + j * width) * 6];

            // define the 6 corners of the two triangles
            float scaledTileSizeX = tileSize.x * scale;
            float scaledTileSizeY = tileSize.y * scale;

            triangles[0].position = sf::Vector2f(i * scaledTileSizeX, j * scaledTileSizeY);
            triangles[1].position = sf::Vector2f((i + 1) * scaledTileSizeX, j * scaledTileSizeY);
            triangles[2].position = sf::Vector2f(i * scaledTileSizeX, (j + 1) * scaledTileSizeY);
            triangles[3].position = sf::Vector2f(i * scaledTileSizeX, (j + 1) * scaledTileSizeY);
            triangles[4].position = sf::Vector2f((i + 1) * scaledTileSizeX, j * scaledTileSizeY);
            triangles[5].position = sf::Vector2f((i + 1) * scaledTileSizeX, (j + 1) * scaledTileSizeY);

            // define the 6 matching texture coordinates
            // set triangle[0] == Grass
            triangles[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            // set triangle[1] == Water
            triangles[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            // set triangle[2] == Tree
            triangles[2].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
            // set triangle[3] == stone
            triangles[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
            triangles[4].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            triangles[5].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
        }
    return true;
}

void TileMap::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    // apply the transform
    states.transform *= getTransform();
    // apply the tileset texture
    states.texture = &m_tileset;
    // draw the vertex array
    target.draw(m_vertices, states);
}

sf::Vector2u TileMap::getTileSize() const {
    std::cout << tileSize.x << " X \n";
    std::cout << tileSize.y << " Y \n";
    return sf::Vector2u();
}




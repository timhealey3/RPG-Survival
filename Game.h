#ifndef RPGGAME_GAME_H
#define RPGGAME_GAME_H

#include "Player.h"
#include "Enemy.h"
#include "Item.h"
#include "Tiles.h"
#include "chests.h"
#include <sstream>

class Game {
private:
    sf::Clock clock;
    Player* player;
    Enemy* enemy;
    TileMap* map;
    TileMap* background;
    Chest* chest;
    Item* item;
    std::vector<Enemy*> enemies;
    std::vector<Chest*> chests;
    sf::RenderWindow* window;
    sf::View player_view;
    int maxSpawn;
    float spawnTimer;
    float spawnTimerMax;
    float attackDelay;
    sf::RectangleShape playerHpBar;
    sf::RectangleShape playerHpBarBack;
    sf::Font font;
    sf::Text itemText;
    sf::Text durabilityText;
    sf::Text pointText;
    sf::Text gameOverText;
    sf::Sprite worldBackground;
    sf::Texture worldBackgroundTex;
    void initGui();
    void initWindow();
    void initPlayer();
    void initVariables();
public:
    Game();
    virtual ~Game();
    void run();
    void render();
    void spawnChest();
    void spawnEnemy();
    void moveEnemy();
    void updatePollEvents();
    void updateInput();
    void update();
    void updateGUI();
    sf::Vector2f normalize(sf::Vector2<float> source);
    float calculateDistance(const sf::Vector2f &vector2, const sf::Vector2f &vector21);
    void renderGUI();
    bool collisionDetect(float nextPosX, float nextPosY);
};


#endif //RPGGAME_GAME_H

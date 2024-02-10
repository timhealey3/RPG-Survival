#ifndef RPGGAME_GAME_H
#define RPGGAME_GAME_H

#include "Player.h"
#include "Enemy.h"
#include "Item.h"
#include "Tiles.h"
#include "chests.h"

class Game {
private:
    Player* player;
    Enemy* enemy;
    TileMap* map;
    Chest* chest;
    Item* item;
    std::vector<Enemy*> enemies;
    std::vector<Chest*> chests;
    sf::RenderWindow* window;
    sf::View player_view;
    int maxSpawn;
    float spawnTimer;
    float spawnTimerMax;
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
};


#endif //RPGGAME_GAME_H

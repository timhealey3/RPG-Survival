#ifndef RPGGAME_GAME_H
#define RPGGAME_GAME_H

#include "Player.h"
#include "Enemy.h"
#include "Item.h"
#include "Tiles.h"
#include "chests.h"

class Game {
private:
    sf::Clock clock;
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
    float attackDelay;
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
    sf::Vector2f normalize(sf::Vector2<float> source);

    float calculateDistance(const sf::Vector2f &vector2, const sf::Vector2f &vector21);
};


#endif //RPGGAME_GAME_H

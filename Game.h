#ifndef RPGGAME_GAME_H
#define RPGGAME_GAME_H

#include "Player.h"
#include "Enemy.h"

class Game {
private:
    Player* player;
    Enemy* enemy;
    std::vector<Enemy*> enemies;
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
    void spawnEnemy();
    void moveEnemy();
    void updatePollEvents();
    void updateInput();
    void update();
};


#endif //RPGGAME_GAME_H

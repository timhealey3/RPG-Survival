#ifndef RPGGAME_GAME_H
#define RPGGAME_GAME_H

#include "Player.h"
#include "Enemy.h"
#include "Item.h"
#include "Tiles.h"
#include "chests.h"
#include "Level.h"
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
    Level* level;
    std::vector<Enemy*> enemies;
    std::vector<Chest*> chests;
    sf::RenderWindow* window;
    sf::View player_view;
    int maxSpawn;
    int clockGameOver = 0;
    int clockGameLevel = 0;
    int clockGameLevelOut = 254;
    int fadeCompleteLevel = 255;
    int fadeComplete = 255;
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
    sf::Text restartText;
    sf::Text levelText;
    sf::Sprite worldBackground;
    sf::Texture worldBackgroundTex;
    void initGui();
    void initWindow();
    void initPlayer();
    void initVariables();
public:
    Game();
    virtual ~Game();
    void restartGame();
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

    void initMap();

    void initLevel();
};


#endif //RPGGAME_GAME_H

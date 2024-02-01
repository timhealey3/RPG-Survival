#include "Game.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

Game::Game() {
    this->initWindow();
    this->initPlayer();
    this->initVariables();
    player_view.setCenter(this->window->getSize().x / 2, this->window->getSize().y / 2);
    player_view.setSize(this->window->getSize().x, this->window->getSize().y);
    this->window->setView(player_view);
    const int level[] =
            {
                    2, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                    2, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,
                    2, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
                    2, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0,
                    2, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0,
                    2, 1, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0,
                    2, 1, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,
                    2, 1, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
            };
    if (!map->load("/Users/timhealey/CLionProjects/rpgGame/Tileset/tileSet.png", sf::Vector2u(32, 32), level, 16, 8, 4.f))
        std::cout << "map did NOT load";
}

Game::~Game() {
    delete this->window;
    delete this->player;
    delete this->map;
    for (auto& enemy : enemies) {
        // TODO implement A* to move enemy
        delete enemy;
    }
}

void Game::initVariables() {
    this->spawnTimerMax = 60.f;
    this->spawnTimer = 30.f;
    this->maxSpawn = 5;
}

void Game::initPlayer()
{
    this->player = new Player();
    this->map = new TileMap();
    this->player->setPosition(500.f, 500.f);
}

void Game::run() {
    while(this->window->isOpen()) {
        this->updatePollEvents();
        this->update();
        this->render();
    }
}

void Game::updatePollEvents() {
    sf::Event e;
    while (this->window->pollEvent(e)) {
        if (e.Event::type == sf::Event::Closed)
            this->window->close();
        if (e.Event::key.code == sf::Keyboard::Escape)
            this->window->close();
    }
}

void Game::update() {
    this->updateInput();
    this->spawnEnemy();
    this->moveEnemy();
    this->player->update();
}

void Game::updateInput() {
    // move player
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        // move to the left. if water or tree do not move
        float tileSizeX = static_cast<float>(map->getTileSize().x);
        int playerTileX = static_cast<int>((this->player->getPos().x + this->player->getBounds().width / 2) / tileSizeX);
        int playerTileY = static_cast<int>((this->player->getPos().y + this->player->getBounds().height / 2) / map->getTileSize().y);
        std::cout << "Tile X " << playerTileX << "\n";
        std::cout << "Tile Y " << playerTileY << "\n";
        std::cout << "Player Pos X: " << this->player->getPos().x << "\n";
        std::cout << "Player Bounds Width: " << this->player->getBounds().width << "\n";
        std::cout << "Tile Size X: " << map->getTileSize().x << "\n";

        this->player->move(-1.f, 0.f);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        this->player->move(1.f, 0.f);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        this->player->move(0.f, -1.f);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        this->player->move(0.f, 1.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->player->canAttack()) {
        std::cout << "attack did " << this->player->getDamage() << "\n";
    }
}

bool Game::collisionDetection(float dirX, float dirY) {
    // jf player walking on grass return false, no collision
    // if 0 or 3 no collision
    if (this->player)
        return false;
    // if water or tree return true, there is collison
    // if 1 or 2 collision
    else
        return true;
}

void Game::spawnEnemy() {
    this->spawnTimer += 0.5f;
    // spawn enemies
    if (this->spawnTimer >= this->spawnTimerMax && enemies.size()  < maxSpawn) {
        std::cout << "Enemy Spawned\n";
        this->enemy = new Enemy();
        this->enemy->setPosition(rand() % this->window->getSize().x - 50.f, rand() % this->window->getSize().y - 50.f);
        this->enemies.push_back(enemy);
        this->spawnTimer = 0.f;
    }
}

void Game::moveEnemy() {
    for (auto& enemy : enemies) {
        // TODO implement A* to move enemy
        enemy->moveEn(0.f, -.5f);
    }
}

void Game::initWindow() {
    this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Stay Alive for Rome", sf::Style::Close | sf::Style::Titlebar);
    this->window->setFramerateLimit(60);
    this->window->setVerticalSyncEnabled(false);
}

void Game::render() {
    this->window->clear();
    player_view.setCenter(player->getPos());
    this->window->setView(player_view);
    this->window->draw(*map);
    this->player->render(*this->window);
    for (auto& enemy : enemies) {
        enemy->render(*this->window);
    }
    this->window->display();
}

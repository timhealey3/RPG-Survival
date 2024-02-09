#include "Game.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

Game::Game() {
    this->initWindow();
    this->initPlayer();
    this->initVariables();
    this->spawnChest();
    player_view.setCenter(this->window->getSize().x / 2, this->window->getSize().y / 2);
    player_view.setSize(this->window->getSize().x, this->window->getSize().y);
    this->window->setView(player_view);
    const int level[] =
            {
                    3, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                    3, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0,
                    3, 0, 0, 3, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
                    3, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 1, 1, 0, 0, 3,
                    3, 0, 0, 0, 3, 3, 3, 0, 0, 0, 1, 1, 0, 2, 0, 3,
                    0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 3,
                    0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 1, 0, 3, 0,
                    0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 1, 3, 3, 0,
            };
    // TODO come up with map and player position
    if (!map->load("/Users/timhealey/CLionProjects/rpgGame/Tileset/tileSet.png", sf::Vector2u(32, 32), level, 16, 8, 4.f))
        std::cout << "map did NOT load";
}

Game::~Game() {
    delete this->window;
    delete this->player;
    delete this->map;
    for (Chest* chest : this->chests) {
        delete chest;
    }
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
    // open chests
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && this->player->canAttack()) {
        for (auto &chest: chests) {
            float distance = std::sqrt(std::pow(chest->getPos().x - this->player->getPos().x, 2) +
                                       std::pow(chest->getPos().y - this->player->getPos().y, 2));
            if (distance <= 90.0f ) {
                if (chest->getGold() <= this->player->getGold()) {
                    std::cout << chest->getGold() << std::endl;
                }
                else {
                    std::cout << chest->getGold() << " costs, you only have " << this->player->getGold() << std::endl;
                }
            }
        }
    }
    // attack
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->player->canAttack()) {
        for (auto &enemy : enemies) {
            if (this->player->getBounds().intersects(this->enemy->getPos())) {
                std::cout << "attack did " << this->player->getDamage() << "\n";
            }
        }
    }
    // move player
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {        // move to the left. if water or tree do not move
        //std::cout << this->map->getTileSize().x << " in Game\n";
        this->player->move(-1.f, 0.f);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        this->player->move(1.f, 0.f);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        this->player->move(0.f, -1.f);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        this->player->move(0.f, 1.f);

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
    for (auto& chest : chests) {
        chest->render(*this->window);
    }
    this->player->render(*this->window);
    for (auto& enemy : enemies) {
        enemy->render(*this->window);
    }
    this->window->display();
}

void Game::spawnChest() {
    for (int j = 0; j < 5; j++) {
        this->chests.push_back(new Chest());
    }
}

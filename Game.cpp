#include "Game.h"
#include <iostream>
#include <cmath>

Game::Game() {
    this->initWindow();
    this->initPlayer();
    this->initGui();
    this->initVariables();
    this->spawnChest();
    player_view.setCenter(this->window->getSize().x / 2, this->window->getSize().y / 2);
    player_view.setSize(this->window->getSize().x, this->window->getSize().y);
    this->window->setView(player_view);
    const int level[] =
            {
                    3, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                    3, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                    3, 0, 0, 3, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
                    3, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 3,
                    3, 0, 0, 0, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3,
                    0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,
                    0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0,
                    0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0,
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
        delete enemy;
    }
}

void Game::initVariables() {
    this->spawnTimerMax = 60.f;
    this->spawnTimer = 30.f;
    this->maxSpawn = 5;
    this->attackDelay = 0.5f;
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
        this->updateGUI();
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
    for (auto& enemy : enemies) {
        enemy->update();
    }
}

void Game::updateInput() {
    // open chests
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && this->player->canAttack()) {
        for (auto &chest: chests) {
            float distance = std::sqrt(std::pow(chest->getPos().x - this->player->getPos().x, 2) +
                                       std::pow(chest->getPos().y - this->player->getPos().y, 2));
            if (distance <= 90.0f ) {
                if (chest->getGold() <= this->player->getGold()) {
                    if (!chest->getOpened()) {
                        const Item *chestItem = chest->getItem();
                        if (chestItem) {
                            std::cout << "Name: " << chestItem->getItemName() << " Damage: " << chestItem->getDamage()
                                      << std::endl;
                            this->player->subGold(chest->getGold());
                            this->player->setItem(chestItem);
                        }
                    }
                    else {
                        std::cout << "Chest has no item." << std::endl;
                    }
                }
                else {
                    std::cout << chest->getGold() << " costs, you only have " << this->player->getGold() << std::endl;
                }
            }
        }
    }
    // attack
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->player->canAttack()) {
        this->player->setAnimationFacing(3);
        for (auto it = enemies.begin(); it != enemies.end();) {
            // if player is facing a direction. only on sword animation
            if (this->player->getSwordBounds().intersects((*it)->getPos())) {
                std::cout << "before HP " << (*it)->getHp() << std::endl;
                (*it)->setHPDmg(this->player->getItem()->getDamage());
                std::cout << this->player->getItem()->getDurability() << std::endl;

                this->player->getItem()->setDurability(1);

                if (this->player->getItem()->getDurability() <= 0) {
                    std::cout << "Your Item Broke!" << std::endl;
                    this->player->brokeItem();
                }
                std::cout << "attack did " << this->player->getItem()->getDamage() << "\n";
                // if killed enemy
                if ((*it)->getHp() <= 0) {
                    this->player->addGold((*it)->getGold());
                    it = enemies.erase(it);
                    break;
                } else {
                    ++it;
                }
            } else {
                ++it;
            }
        }
    }

    // move player
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        this->player->setAnimationFacing(1);
        this->player->move(-1.f, 0.f);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        this->player->setAnimationFacing(2);
        this->player->move(1.f, 0.f);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        this->player->setAnimationFacing(4);
        this->player->move(0.f, -1.f);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        this->player->setAnimationFacing(4);
        this->player->move(0.f, 1.f);
    }
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
        !sf::Keyboard::isKeyPressed(sf::Keyboard::D) &&
        !sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
        !sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        this->player->setAnimationFacing(0);
    }
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
        sf::Vector2f direction = normalize(player->getPos() - enemy->getLocalPos());
        float distance = calculateDistance(player->getPos(), enemy->getLocalPos());
        float distanceThreshold = 56.0f;
        if (distance > distanceThreshold) {
            float adjustedSpeed = std::min(enemy->getMovementSpeed(), distance);
            enemy->moveEn(direction.x * adjustedSpeed, direction.y * adjustedSpeed);
        }
        else {
            //this->player->setHp(enemy->getDmg());
            if (enemy->canAttack()) {
                this->player->setHp(1);
            }
        }
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
    this->renderGUI();
    //if (this->player->getGold() <= 0)
    //    this->window->draw(this->gameOverText);
    this->window->display();
}

void Game::spawnChest() {
    for (int j = 0; j < 5; j++) {
        this->chests.push_back(new Chest());
    }
}

sf::Vector2f Game::normalize(sf::Vector2<float> source) {
    float length = sqrt((source.x * source.x) + (source.y * source.y));
    if (length != 0)
        return {source.x / length, source.y / length};
    else
        return source;
}

float Game::calculateDistance(const sf::Vector2f& pos1, const sf::Vector2f& pos2) {
    return std::sqrt((pos1.x - pos2.x) * (pos1.x - pos2.x) + (pos1.y - pos2.y) * (pos1.y - pos2.y));
}

void Game::initGui() {
    if (!this->font.loadFromFile("/Users/timhealey/CLionProjects/rpgGame/Tileset/IMMORTAL.ttf"))
        std::cout << "ERROR::GAME::FAILED LOAD FONT" << "\n";

    // Set up point text
    this->pointText.setFont(this->font);
    this->pointText.setCharacterSize(24);
    this->pointText.setFillColor(sf::Color::White);

    this->itemText.setFont(this->font);
    this->itemText.setCharacterSize(24);
    this->itemText.setFillColor(sf::Color::White);
    // Set up game over text
    this->gameOverText.setFont(this->font);
    this->gameOverText.setCharacterSize(50);
    this->gameOverText.setFillColor(sf::Color::Red);
    this->gameOverText.setString("Game Over!");

    // Position game over text at the center of the screen
    sf::Vector2f viewTopLeft = this->window->getView().getCenter() - this->window->getView().getSize() / 2.f;
    this->pointText.setPosition(viewTopLeft.x + 10.f, viewTopLeft.y + 10.f);
    this->playerHpBar.setSize(sf::Vector2f(300.f, 25.f));
    this->playerHpBar.setFillColor(sf::Color::Green);
    this->playerHpBar.setPosition(sf::Vector2f(20.f, 20.f));
    this->playerHpBarBack = this->playerHpBar;
    this->playerHpBarBack.setFillColor(sf::Color::Red);
}


void Game::renderGUI()
{
    sf::Vector2f viewTopLeft = this->window->getView().getCenter() - this->window->getView().getSize() / 2.f;
    this->pointText.setPosition(viewTopLeft.x + 10.f, viewTopLeft.y + 10.f);
    this->window->draw(this->pointText);
    this->window->draw(this->itemText);
    this->playerHpBarBack.setPosition(viewTopLeft.x + 10.f, viewTopLeft.y + 10.f);
    this->window->draw(this->playerHpBarBack);
    this->playerHpBar.setPosition(viewTopLeft.x + 10.f, viewTopLeft.y + 10.f);
    this->window->draw(this->playerHpBar);
}

void Game::updateGUI()
{
    std::stringstream ss;
    std::stringstream itemStream;
    ss << "\nGold: " << this->player->getGold() << "\n";
    ss << "Item: " << this->player->getItem()->getItemName();
    this->pointText.setString(ss.str());
    this->itemText.setString(itemStream.str());
    float hpPercent = static_cast<float>(this->player->getHp()) / this->player->getHpMax();
    this->playerHpBar.setSize(sf::Vector2f(300.f* hpPercent, this->playerHpBar.getSize().y));
}
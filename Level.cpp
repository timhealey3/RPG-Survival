//
// Created by Tim Healey on 2/20/24.
//

#include "Level.h"

Level::Level() {
    initVariables();
}

Level::~Level() {

}

void Level::initVariables() {
    this->levelNum = 0;
}

int Level::getLevel() {
    return levelNum;
}

void Level::setLevel(int newLevel) {
    this->levelNum = newLevel;
    this->spawnedNum = 0;
    this->aliveNum = 0;
    this->spawnedMax = 0;
}

void Level::increaseLevel(int increaseAmount) {
    this->levelNum += increaseAmount;
}

bool Level::checkComplete(int alive) {
    // certain enemies spawned
    // if x amount spawned
    // 0 enemies are alive
    if (spawnedNum >= spawnedMax) {
        if (alive == 0) {
            return true;
        }
    }
    return false;
}

void Level::increaseSpawned() {
    this->spawnedNum++;
}

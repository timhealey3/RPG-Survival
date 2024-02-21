//
// Created by Tim Healey on 2/20/24.
//

#include "Level.h"

Level::Level() {
    initVariables();
    setValues();
}

Level::~Level() {

}

void Level::initVariables() {
    this->levelNum = 1;
}

int Level::getLevel() const {
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

bool Level::getSpawnedLimit() const {
    if (this->spawnedNum == this->spawnedMax) {
        return true;
    }
    return false;
};

bool Level::checkComplete() const {
    // certain enemies spawned
    // if x amount spawned
    // 0 enemies are alive
    if (spawnedNum >= spawnedMax) {
            return true;
    }
    return false;
}

void Level::increaseSpawned() {
    this->spawnedNum++;
}

void Level::setValues() {
    if (levelNum == 1) {
        this->spawnedMax = 2;
    }
}

//
// Created by Tim Healey on 2/20/24.
//

#ifndef RPGGAME_LEVEL_H
#define RPGGAME_LEVEL_H


class Level {
private:
    int levelNum;
    int spawnedNum;
    int spawnedMax;
    int aliveNum;
    void initVariables();
public:
    Level();
    virtual ~Level();
    int getLevel();
    int setLevelStats();
    void increaseLevel(int increaseAmount);
    void setLevel(int newLevel);
    bool checkComplete(int alive);

    void increaseSpawned();
};


#endif //RPGGAME_LEVEL_H

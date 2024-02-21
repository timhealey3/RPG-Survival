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
    int getLevel() const;
    int setLevelStats();
    void setValues();
    void increaseLevel(int increaseAmount);
    void setLevel(int newLevel);
    bool checkComplete(int alive) const;

    void increaseSpawned();

    bool getSpawnedLimit() const;

    bool checkComplete() const;
};


#endif //RPGGAME_LEVEL_H

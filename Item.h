#ifndef RPGGAME_ITEM_H
#define RPGGAME_ITEM_H
#include <string>

class Item {
private:
    int damage;
    std::string Name;
    void initVariables();
public:
    Item();
    virtual ~Item();
};


#endif //RPGGAME_ITEM_H

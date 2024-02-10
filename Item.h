#ifndef RPGGAME_ITEM_H
#define RPGGAME_ITEM_H
#include <string>

class Item {
private:
    int damage;
    std::string Name;
    void initVariables(const std::string& itemName, int damageVar);
public:
    Item(const std::string& itemName, int damageVar);
    virtual ~Item();
    const int getDamage() const;
    const std::string getItemName() const;
    void setDamage(int newDamage);
};


#endif //RPGGAME_ITEM_H

#ifndef RPGGAME_ITEM_H
#define RPGGAME_ITEM_H
#include <string>

class Item {
private:
    int damage;
    std::string Name;
    int Durability;
    void initVariables(const std::string& itemName, int damageVar, int durabilityVar);
public:
    Item(const std::string& itemName, int damageVar, int durabilityVar);
    virtual ~Item();
    const int getDamage() const;
    const int getDurability() const;
    const std::string getItemName() const;
    void setDurability(int durabilitySub);
    void setDamage(int newDamage);
};


#endif //RPGGAME_ITEM_H

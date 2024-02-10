//
// Created by Tim Healey on 1/28/24.
//

#include "Item.h"

Item::Item(const std::string &itemName, int damageVar) {
    initVariables(itemName, damageVar);
}

Item::~Item() {

}

void Item::initVariables(const std::string &itemName, int damageVar) {
    this->damage = damageVar;
    this->Name = itemName;
}

void Item::setDamage(int newDamage) {
    this->damage = newDamage;
}

const std::string Item::getItemName() const {
    return this->Name;
}

const int Item::getDamage() const {
    return this->damage;
}





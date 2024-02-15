//
// Created by Tim Healey on 1/28/24.
//

#include "Item.h"

Item::Item(const std::string &itemName, int damageVar, int durabilityVar) {
    initVariables(itemName, damageVar, durabilityVar);
}

Item::~Item() {

}

void Item::initVariables(const std::string &itemName, int damageVar, int durabilityVar) {
    this->damage = damageVar;
    this->Name = itemName;
    this->Durability = durabilityVar;
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

const int Item::getDurability() const {
    return this->Durability;
}

void Item::setDurability(int durabilitySub) {
    this->Durability -= durabilitySub;
}





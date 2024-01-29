//
// Created by Tim Healey on 1/28/24.
//

#include "Item.h"

Item::Item() {
    initVariables();
}

Item::~Item() {

}

void Item::initVariables() {
    this->damage = 10;
    this->Name = "Excalibur";
}

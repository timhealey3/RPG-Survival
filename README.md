## RPG Survival Game

### Design Document

Language: C++

Library: SFML

Graphics: 2D Sprites

Sound Design:

Setting: Britain 55 BC. 

Plot: Julius Ceasar invaded Britain with his Roman legion. You are one of his loyal soldiers, but in the chaos of the invasion you were lost. Survive alone as waves of enemies attack, and after 7 nights you will be reunited with your Roman legion.

Items: Sword, Potions

Chests: Store Items randomly around the map with stats that are equal to the chest level. Chests can be either opened or closed, once open they are empty and can not be opened or closed again.

Abilities: Lightning bolt from Jupiter, Water wave from Neptune, Fury from Mars

Stats: Player advances stats from getting better swords. Swords have two stats, durability and damage. Once durability hits zero, the sword breaks and is deleted.

Player: Attack, Health, Abilities, Movement, Equip Items, Use Items, Interact (open chests)

Enemy: Health, A* pathfinding, Spawn, Attack

Boss <Enemy>: Same as enemy but sprite is bigger and better stats

Map <tiles>: The map is compromised of tiles. Player can walk on map consisting of grass and cobblestone tiles.

#pragma once
#include <iostream>

/**
 * @enum EntityType
 * @brief Enum class that represent the Type of the Entity: Player,Mob,Item
 */
enum class EntityType {
    PLAYER,
    MOB,
    ITEM,
    VOID
};

enum class Direction {
    RIGHT,
    LEFT,
    UP,
    DOWN,
    NONE
};
#pragma once
#include <iostream>
#include <functional>

/**
 * @struct Position
 * @brief Represent a position on the board.
 * @param x X coord
 * @param y Y coord
 */
struct Position {
    int x;
    int y;

    Position(int x = 0,int y = 0) : x(x), y(y) {}

    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }

};
namespace std {
    template<>
    struct hash<Position> {
        std::size_t operator()(const Position& pos) const noexcept {
            std::size_t h1 = std::hash<int>{}(pos.x);
            std::size_t h2 = std::hash<int>{}(pos.y);
            return h1 ^ (h2 << 1); // Combine les deux
        }
    };
}
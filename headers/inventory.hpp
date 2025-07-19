#pragma once
#include <iostream>
#include <vector>
#include "classes.hpp"

class Item;

class Inventory {
private:
    std::vector<std::unique_ptr<Item>> items;
    static constexpr size_t MAX_INV_SIZE = 5;
public:
    Inventory();
    bool addItem(std::unique_ptr<Item> item);
    void removeItem(const std::string& name);
    void removeFirstItem();
    const std::vector<std::unique_ptr<Item>>& getItems() const;
    size_t getSize() const;
    size_t getMaxSize() const;
    bool isEmpty();
};
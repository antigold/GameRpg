#include <iostream>
#include "inventory.hpp"

Inventory::Inventory(){};

bool Inventory::addItem(std::unique_ptr<Item> item){
    if (items.size() >= MAX_INV_SIZE){
        return false;
    }
    items.push_back(std::move(item));
    return true;
}

void Inventory::removeItem(const std::string& itemName){
    for (auto i = items.begin(); i != items.end(); ++i){
        if ((*i)->getName() == itemName){
            items.erase(i);
            return;
        }
    }
}

void Inventory::removeFirstItem(){
    if (!items.empty()){
        auto i = items.begin();
        items.erase(i);
    }
}

const std::vector<std::unique_ptr<Item>>& Inventory::getItems() const {
    return items;
} 

size_t Inventory::getSize() const {
    return items.size();
}

size_t Inventory::getMaxSize() const {
    return MAX_INV_SIZE;
}

bool Inventory::isEmpty() {
    return items.empty();
}
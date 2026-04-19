#ifndef DUNGEONRPG_INVENTORY_H
#define DUNGEONRPG_INVENTORY_H

#endif //DUNGEONRPG_INVENTORY_H

#include "item.h"

class Inventory {
public:
    Inventory(int capacity) : capacity(capacity) {
        items = new Item*[capacity];
    }

    void addItem(Item* item) {
        if (count >= capacity) {
            std::cout << "The inventory is full\n";
            return;
        }

        items[count] = item;
        count++;
    }

    void deleteItem(int index) {
        delete items[index];

        for (int i = index; i < count - 1; i++) {
            items[i] = items[i + 1];
        }

        count--;
    }

    void printAllItems() const {
        for (int i = 0; i < count; i++) {
            std::cout << "\nCell №" << i << ": \n";
            items[i]->printInfo();
        }
    }

    Item* useItem(int index) const {
        if (index < 0 || index >= count) {
            return nullptr;
        }

        return items[index];
    }

    ~Inventory() {
        for (int i = 0; i < count; i++) {
            delete items[i];
        }

        delete[] items;
    }

private:
    Item** items;
    int capacity = 0; 
    int count = 0; 
};

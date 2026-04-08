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

    void printAllItems() const {
        for (int i = 0; i < count; i++) {
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
        for (int i = 0; i < capacity; i++) {
            delete items[i];
        }

        delete[] items;
    }
private:
    Item** items;
    int capacity = 0; // максимальное количество предметов
    int count = 0; // кол-во предметов в инвентаре
};
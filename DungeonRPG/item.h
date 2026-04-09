#ifndef DUNGEONRPG_ITEM_H
#define DUNGEONRPG_ITEM_H

#endif //DUNGEONRPG_ITEM_H

#include <iostream>

class Item {
public:
    Item() = default;

    Item(std::string itemName, std::string itemType, int itemDamage, int itemHealAmount)
        : itemName(std::move(itemName)), itemType(std::move(itemType)), itemDamage(itemDamage), itemHealAmount(itemHealAmount) {}

    int getItemDamage() const {
        return itemDamage;
    }

    int getItemHealAmount() const {
        return itemHealAmount;
    }

    std::string getItemName() const {
        return itemName;
    }

    std::string getItemType() const {
        return itemType;
    }

    void printInfo() const {
        std::cout << "\n+-Name: " << itemName
                  << "\n+-Type: " << itemType
                  << "\n+-Damage: " << itemDamage
                  << "\n+-Heal amount: " << itemHealAmount << "\n";
    }

private:
    std::string itemName;
    std::string itemType;
    int itemDamage;
    int itemHealAmount;
};

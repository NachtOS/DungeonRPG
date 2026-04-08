#ifndef DUNGEONRPG_CHARACTER_H
#define DUNGEONRPG_CHARACTER_H

#endif //DUNGEONRPG_CHARACTER_H

#include <string>
#include "inventory.h"

class Character {
public:
    Character(std::string name, int maxHealth, int baseDamage)
        : name(std::move(name)), maxHealth(maxHealth), health(maxHealth), baseDamage(baseDamage) {}

    int getHealth() const {
        return health;
    }

    void takeDamage(int damage) {
        health -= damage;
        if (health < 0) {
            health = 0;
        }
        std::cout << name << " received " << damage << " damage! \nHP: " << health << "\n";
    }

    bool isAlive() const {
        return health > 0;
    }

    virtual int attack() {
        return baseDamage;
    }

    virtual ~Character() {}

protected:
    std::string name;
    int maxHealth = 0;
    int health = 0;
    int baseDamage = 0;
};

class Enemy : public Character {
public:
    Enemy(std::string name, std::string enemyType, int maxHealth, int baseDamage, int gold)
        : Character(std::move(name), maxHealth, baseDamage), enemyType(std::move(enemyType)), gold(gold) {}

    int getGold() const {
        return gold;
    }

    std::string getEnemyType() const {
        return enemyType;
    }

    int attack() override {
        return baseDamage;
    }

    std::string getName() const {
        return name;
    }

private:
    int gold = 0;
    std::string enemyType;
};

class Player : public Character {
public:
    Player(std::string name, int maxHealth, int baseDamage, int gold)
        : Character(std::move(name), maxHealth, baseDamage), gold(gold) {
        inventory = new Inventory(9);

        inventory->addItem(new Item("Heal Potion", "potion", 0, 50));
        inventory->addItem(new Item("Heal Potion", "potion", 0, 50));
    }

    Inventory* getInventory() const {
        return inventory;
    }

    void addGold(int goldAmount) {
        gold += goldAmount;
    }

    std::string getName() const {
        return name;
    }

    void playerHeal(int healAmount) {
        health += healAmount;
    }

    int getGold() {
        return gold;
    }

    int attack() override {
        return baseDamage;
    }

    ~Player() { delete inventory; }
private:

    int gold = 0;
    Inventory* inventory;
};
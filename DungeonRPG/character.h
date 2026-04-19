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
    Enemy(std::string name, std::string enemyType, int maxHealth, int baseDamage, int gold, int giveExp)
        : Character(std::move(name), maxHealth, baseDamage), enemyType(std::move(enemyType)), gold(gold), giveExp(giveExp) {}

    int getGold() const {
        return gold;
    }

    int getGiveExp() {
        return giveExp;
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
    int giveExp = 0;
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

    void playerHeal(int healAmount) {
        health += healAmount;
    }

    void addExperience(int experience) {
        this->experience += experience;
    }

    void levelUp() {
        if (level <= 5 && experience >= 100) {
            level++;
            experience -= 100;
        }
        else if (level <= 10 && level > 5 && experience >= 150) {
            level++;
            experience -= 150;
        }
        else if (level > 10 && experience >= 200) {
            level++;
            experience -= 200;
        }
    }

    std::string getName() const {
        return name;
    }

    int getLevel() const {
        return level;
    }

    int getGold() const {
        return gold;
    }

    int getExperince() const {
        return experience;
    }

    int attack() override {
        return baseDamage;
    }

    ~Player() { delete inventory; }

private:
    int experience = 0;
    int level = 0;
    int gold = 0;
    Inventory* inventory;
};

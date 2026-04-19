#ifndef DUNGEONRPG_GAME_H
#define DUNGEONRPG_GAME_H

#endif //DUNGEONRPG_GAME_H

#include "character.h"
#include <iostream>
#include <ctime>

class Game {
public:
    Game() {
        srand(time(0));
        player = new Player("Slayer", 150, 5, 0);
        enemies = new Enemy*[enemyCount];

        enemies[0] = new Enemy("Goblin", "goblin", 40, 12, 30,25);
        enemies[1] = new Enemy("Orc", "orc", 80, 20, 60, 35);
    }

    void shop() {
        bool onShop = true;

        do {
            std::cout << "\n+========= SHOP =========+"
                      << "\n1. Heal Potion       20 Gold"
                      << "\n2. Sword \"Zirael\"  35 Gold"
                      << "\n0. Exit\n";

            std::cout << "Select: ";
            int select = 0;
            std::cin >> select;

            switch (select) {
                case 1:
                    if (player->getGold() >= 20) {
                        player->getInventory()->addItem(new Item("Heal Potion", "Potion", 0, 50));
                        player->addGold(-20);
                    }
                    else {
                        std::cout << "Not enough gold!\n";
                        break;
                    }
                    break;
                case 2:
                    if (player->getGold() >= 35) {
                        player->getInventory()->addItem(new Item("Zirael", "Sword", 25, 0));
                        player->addGold(-35);
                    }
                    else {
                        std::cout << "Not enough gold!\n";
                        break;
                    }
                    break;
                case 0:
                    std::cout << "\nExiting the shop\n";
                    onShop = false;
                    break;
                default:
                    std::cout << "\nThe item does not exist\n";
                    break;
            }
        } while (onShop);
    }

    void playerStatus() {
        std::cout << "Name:  " << player->getName()
                  << "\nDMG:   " << player->attack()
                  << "\nHP:    " << player->getHealth()
                  << "\nLVL:   " << player->getLevel()
                  << "\nEXP:   " << player->getExperince()
                  << "\n\nGold:  " << player->getGold() << "\n";
    }

    void research() {
        int index = rand() % enemyCount;
        fight(enemies[index]);
    }

    void fight(Enemy* enemy) {
        while (player->isAlive() && enemy->isAlive()) {
            std::cout << "\n+==== " << enemy->getName() << " Cave ====+\n"
                      << "1 - Attack\n"
                      << "2 - Use heal potion\n";
            int select = 0;
            std::cin >> select;

            switch (select) {
                case 1:
                    enemy->takeDamage(player->attack());
                    std::cout << "\n" << enemy->getName() << " attacked back.\n";
                    player->takeDamage(enemy->attack());

                    break;
                case 2:
                    std::cout << "Select: ";
                    player->getInventory()->printAllItems();
                    int index;
                    std::cin >> index;

                    Item* item = player->getInventory()->useItem(index);
                    if (item != nullptr) {
                        player->playerHeal(item->getItemHealAmount());
                        std::cout << "You healed for " << item->getItemHealAmount() << " HP!\n";
                    }
                    else {
                        std::cout << "No potions!\n";
                    }

                    player->getInventory()->deleteItem(index);
                    break;
            }
        }

        if (!player->isAlive()) {
            std::cout << "\nGame Over!\n";
            running = false;
        }
        else {
            std::cout << enemy->getName() << " defeated! +" << enemy->getGold() << " gold!\n";

            player->addGold(enemy->getGold()); // Add gold to player after enemy defeated
            player->addExperience(enemy->getGiveExp());
            player->levelUp();

            if (rand() % 2 == 0) {
                player->getInventory()->addItem(new Item("Heal Potion", "potion", 0, 50));
                std::cout << "You found a Heal Potion!\n";
            }
        }
    }

    void start() {
        do {
            mainMenu();
        } while (running);
    }

    void mainMenu() {
        std::cout << "\n+==== Menu ====+\n"
                  << "1 - Research\n"
                  << "2 - Player status\n"
                  << "3 - Shop\n"
                  << "0 - Exit\n";
        int select = 0;
        std::cin >> select;

        switch (select) {
            case 1:
                research();
                break;
            case 2:
                playerStatus();
                break;
            case 3:
                shop();
                break;
            case 0:
                running = false;
                break;
            default:
                std::cout << "Invalid\n";
                break;
        }
    }

    ~Game() {
        delete player;
        for (int i = 0; i < enemyCount; i++) {
            delete enemies[i];
        }

        delete[] enemies;
    }

private:
    Player* player;
    Enemy** enemies;
    int enemyCount = 2;
    bool running = true;
};

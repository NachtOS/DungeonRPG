#ifndef DUNGEONRPG_GAME_H
#define DUNGEONRPG_GAME_H

#endif //DUNGEONRPG_GAME_H

#include "character.h"

#include <iostream>

class Game {
public:
    Game() {
        player = new Player("Slayer", 150, 5, 0);
        enemies = new Enemy*[enemyCount];

        enemies[0] = new Enemy("Goblin", "goblin", 40, 12, 30);
        enemies[1] = new Enemy("Orc", "orc", 80, 20, 60);
    }

    void playerStatus() {
        std::cout << "Name: " << player->getName()
                  << "\nDMG: " << player->attack()
                  << "\nHP: " << player->getHealth() << "\n";
    }

    void research() {
        int index = rand() % enemyCount;
        fight(enemies[index]);
    }

    void fight(Enemy* enemy) {
        while (player->isAlive() && enemy->isAlive()) {
            std::cout << "\n+==== " << enemy->getName() << " Cave ====+\n"
                      << "1 - Atack\n"
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
                    break;
            }
        }

        if (!player->isAlive()) {
            std::cout << "\nGame Over!\n";

        } else {
            std::cout << enemy->getName() << " defeated! +" << enemy->getGold() << " gold!\n";
            player->addGold(enemy->getGold());
        }
    }

    void start() {
        bool running = true;
        do {
            mainMenu(running);
        } while (running);
    }

    void mainMenu(bool& running) {
        std::cout << "\n==== Menu ====\n"
                  << "1 - Research\n"
                  << "2 - Player status\n"
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
};
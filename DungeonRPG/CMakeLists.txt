cmake_minimum_required(VERSION 4.1)
project(DungeonRPG)

set(CMAKE_CXX_STANDARD 20)

add_executable(DungeonRPG DungeonRPG.cpp
        item.h
        inventory.h
        character.h
        game.h
)

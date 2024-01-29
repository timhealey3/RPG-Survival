cmake_minimum_required(VERSION 3.14)

project(rpgGame)
set(CMAKE_CXX_STANDARD 11)
# Set the path to the SFML CMake configuration files
set(SFML_DIR "/opt/homebrew/Cellar/sfml/2.6.1/lib/cmake/SFML")

# Find SFML components
find_package(SFML 2.6.1 COMPONENTS system window graphics REQUIRED)

# Add your source files
add_executable(rpgGame main.cpp Game.cpp
        Player.cpp
        Player.h
        Enemy.cpp
        Enemy.h
        Item.cpp
        Item.h
        Tiles.cpp
        Tiles.h)

# Link SFML libraries
target_link_libraries(rpgGame sfml-system sfml-window sfml-graphics)

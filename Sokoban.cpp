// "Copyright [2024] <Jason Ossai>"
#include "Sokoban.hpp"
#include <iostream>
#include <fstream>

Sokoban::Sokoban() {
    _width = 12;
    _height = 12;
}

std::istream& operator>>(std::istream& is, Sokoban& game) {
    is >> game._height >> game._width;
    game.grid.resize(game._height, std::vector<char>(game._width));

    for (int i = 0; i < game._height; i++) {
        for (int j = 0; j < game._width; j++) {
            is >> game.grid[i][j];
            if (game.grid[i][j] == '@') {
                game.playerPosition = { j, i };
            }
        }
    }
    return is;
}

Sokoban::Sokoban(const std::string& levelFilename) {
    // Load the textures
    if (!wallTexture.loadFromFile("block_06.png") ||
        !playerTexture.loadFromFile("player_05.png") ||
        !boxTexture.loadFromFile("crate_03.png") ||
        !storageTexture.loadFromFile("ground_04.png") ||
        !emptyStoragetexture.loadFromFile("ground_01.png")) {
        std::cerr << "Failed to load one or more textures." << std::endl;
    }
    playerSprite.setTexture(playerTexture);
    // Read the level from the file
    std::ifstream inFile(levelFilename);
    if (!inFile) {
        std::cerr << "Failed to open level file: " << levelFilename << std::endl;
        return;
    }
    inFile >> *this;  // This uses the overloaded >> operator to read the level
    inFile.close();
}

int Sokoban::width() const {
    return _width;
}

int Sokoban::height() const {
    return _height;
}

bool Sokoban::movePlayer(Direction direction) {
    sf::Vector2i movep(0, 0);

    // Determine the movement direction
    switch (direction) {
    case Up:
        movep.y = -1;
        break;
    case Down:
        movep.y = 1;
        break;
    case Left:
        movep.x = -1;
        break;
    case Right:
        movep.x = 1;
        break;
    }

    // Calculate the new position
    sf::Vector2i newPosition = playerPosition + movep;

    // Check boundaries
    if (newPosition.x < 0 || newPosition.x >= _width ||
        newPosition.y < 0 || newPosition.y >= _height) {
        return false;
    }

    char targetT = grid[newPosition.y][newPosition.x];
    if (targetT == '#') {  // Wall tile
        return false;
    }
    else if (targetT == 'A' || targetT == '1') {  // Box or Box on storage
        sf::Vector2i boxNewPosition = newPosition + movep;
        char nextTile = grid[boxNewPosition.y][boxNewPosition.x];

        // Check if the box can be pushed
        if (nextTile == '.' || nextTile == 'a') {
            if (nextTile == 'a') {
                grid[boxNewPosition.y][boxNewPosition.x] = '1';   // Box on storage
            }
            else {
                grid[boxNewPosition.y][boxNewPosition.x] = 'A';   // Just the box
            }

            // Update box's old position
            if (targetT == '1') {
                grid[newPosition.y][newPosition.x] = 'a';  // Empty storage spot
            }
            else {
                grid[newPosition.y][newPosition.x] = '.';  // Empty spot
            }
        }
        else {
            // Box cannot be moved
            return false;
        }
    }

    // Move the player
    if (grid[playerPosition.y][playerPosition.x] == '1') {
        grid[playerPosition.y][playerPosition.x] = 'a';
    }
    else {
        grid[playerPosition.y][playerPosition.x] = '.';
    }
    playerPosition = newPosition;
    grid[playerPosition.y][playerPosition.x] = '@';  // Update the new position with the player

    return true;
}

bool Sokoban::isWon() const {
    int boxsesStorage = 0;
    int emptyStorage = 0;
    for (int i = 0; i < _height; i++) {
        for (int j = 0; j < _width; j++) {
            if (grid[i][j] == 'A') {
                boxsesStorage++;
            }
            else if (grid[i][j] == 'a') {
                emptyStorage++;
            }
        }
    }
    return boxsesStorage == 0 || emptyStorage == 0;
}

void Sokoban::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (int i = 0; i < _height; i++) {
        for (int j = 0; j < _width; j++) {
            sf::Sprite sprite;

            char cChar = grid[i][j];
            if (cChar == '#') {
                sprite.setTexture(wallTexture);
            }
            else if (cChar == '@') {
                sprite.setTexture(playerTexture);
            }
            else if (cChar == 'A') {
                sprite.setTexture(boxTexture);
            }
            else if (cChar == 'a') {
                sprite.setTexture(storageTexture);
            }
            else if (cChar == '.') {
                sprite.setTexture(emptyStoragetexture);
            }
            else if (cChar == '1') {
                sprite.setTexture(boxTexture);
            }
            else {
                continue;
            }

            sprite.setPosition(j * TILE_SIZE, i * TILE_SIZE);
            target.draw(sprite, states);
        }
    }
}

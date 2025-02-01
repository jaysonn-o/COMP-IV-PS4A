// Copyright [2024] <Jason Ossai>

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Sokoban.hpp"

int main() {
    // Initialize the game with the level file
    Sokoban game("level1.lvl");

    // Create a window based on the game's dimensions and tile size
    sf::RenderWindow window(sf::VideoMode(game.width() * Sokoban::TILE_SIZE,
        game.height() * Sokoban::TILE_SIZE),
        "Sokoban");

    // Enable vertical synchronization for smoother rendering
    window.setVerticalSyncEnabled(true);

    // Main game loop
    while (window.isOpen()) {
        sf::Event event;

        // Process events
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();  // Close the window if the close event is triggered
            }

            if (event.type == sf::Event::KeyPressed) {
                Direction dir;  // Declare direction variable
                bool validMove = true;  // Flag to track valid movement

                // Determine direction based on key pressed
                switch (event.key.code) {
                case sf::Keyboard::Left:
                    dir = Left;
                    break;
                case sf::Keyboard::Right:
                    dir = Right;
                    break;
                case sf::Keyboard::Up:
                    dir = Up;
                    break;
                case sf::Keyboard::Down:
                    dir = Down;
                    break;
                default:
                    validMove = false;  // Invalid key pressed
                    break;  // Ignore other key presses
                }

                // Move the player if the direction is valid
                if (validMove) {
                    game.movePlayer(dir);
                }
            }
        }

        // Clear the window for the next frame
        window.clear();

        // Draw the game state
        window.draw(game);

        // Display the updated frame
        window.display();
    }

    return 0;
}

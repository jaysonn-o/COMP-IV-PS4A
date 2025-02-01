// "Copyright [2024] <Jason Ossai>"
#ifndef SOKOBAN_HPP
#define SOKOBAN_HPP

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

enum Direction {
    Up,
    Down,
    Left,
    Right
};

class Sokoban : public sf::Drawable {
public:
    Sokoban();
    explicit Sokoban(const std::string& levelFilename);
    static const int TILE_SIZE = 64;
    std::vector<std::vector<char>> grid;
    bool movePlayer(Direction direction);
    bool isWon() const;
    int width() const;
    int height() const;
    sf::Vector2i playerPosition;
    friend std::istream& operator>>(std::istream& is, Sokoban& game);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    int _width;
    int _height;
    sf::Texture wallTexture;
    sf::Texture playerTexture;
    sf::Texture boxTexture;
    sf::Texture storageTexture;
    sf::Texture emptyStoragetexture;
    sf::Sprite playerSprite;
};

#endif // SOKOBAN_HPP

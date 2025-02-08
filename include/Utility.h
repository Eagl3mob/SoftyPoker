#ifndef UTILITY_H
#define UTILITY_H

#include <SFML/Graphics.hpp>
#include <string>

void resizeBackground(sf::RenderWindow& window, sf::Sprite& backgroundSprite, sf::Texture& backgroundTexture);

std::string getAssetPath(const std::string& relativePath);

#endif // UTILITY_H

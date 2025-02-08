#ifndef TEXT_SCROLL_H
#define TEXT_SCROLL_H

#include <SFML/Graphics.hpp>

class TextScroll : public sf::Drawable {
public:
    TextScroll(const sf::Font& font, const std::string& text, float speed, float startY);
    void update(sf::Time elapsed);
    void setCharacterSize(unsigned int size);
    void setPosition(float x, float y);
    void setPosition(sf::Vector2f position);
    void setTextColor(const sf::Color& color);
    sf::Vector2f getPosition() const;
    sf::FloatRect getLocalBounds() const;


private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Text text;
    float speed;
};

#endif // TEXT_SCROLL_H

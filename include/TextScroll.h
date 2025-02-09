#ifndef TEXT_SCROLL_H
#define TEXT_SCROLL_H

#include <SFML/Graphics.hpp>

class TextScroll : public sf::Drawable {
public:
    TextScroll(const sf::Font& font, const std::string& textStr, float speed, float startY, float windowWidth);

    void setTextColor(const sf::Color& color);
    void enableSmoothColorTransition(bool enable);
    void update(sf::Time elapsed, sf::Time totalElapsed); // Ensure it has both parameters
    void setCharacterSize(unsigned int size);
    void setPosition(float x, float y);
    void setPosition(sf::Vector2f position);
    sf::Vector2f getPosition() const;
    sf::FloatRect getLocalBounds() const;
    void setWindowWidth(float width);
    void setColorFadeSpeed(float speed);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::Text text;
    float speed;
    float windowWidth;
    bool enableColorTransition;
    float colorFadeSpeed;
};

#endif // TEXT_SCROLL_H

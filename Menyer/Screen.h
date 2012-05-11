#ifndef SCREEN_H
#define SCREEN_H

#include <sfml/Graphics.hpp>

class Screen : public sf::Drawable
{
    public:
        bool isMouseOver(const sf::Vector2i& mousePos);
        int click(const sf::Vector2i& mousePos);
    protected:
    private:
};

#endif // SCREEN_H

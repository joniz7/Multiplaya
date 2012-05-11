#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include <sfml/Graphics.hpp>
#include <string>

class TextField : public sf::Drawable
{
    public:
        TextField(const float xPos, const float yPos, const int width, const int height);
        virtual ~TextField();

        void setText(std::string text);
        std::string getText();

        void setBackgroundColor(sf::Color color);
        sf::Color getBackgroundColor();

        void setFontColor();
        void setFontSize();

        // set text input to left and middle in height all the time

    protected:
    private:
        sf::Shape* background;
        sf::Text* text;

        virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;
};

#endif // TEXTFIELD_H

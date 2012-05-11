#ifndef BUTTON_H
#define BUTTON_H

#include <sfml/Graphics.hpp>
#include <string>

class Button : public sf::Drawable
{


    public:
       enum TextAlignment {
          LEFT,
          CENTER,
          RIGHT
       };
        // use vector for pos instead? or the points where button should be placed
        Button(const float xPos, const float yPos, const int width, const int height, std::string text );
        Button(int xPos, int yPos, int width, int height);

        virtual ~Button();

        void setFont(const sf::Font &font);
        void setFontColor(const sf::Color &color);
        void setFontStyle(sf::Text::Style style);
        void setFontSize(unsigned int size);
        void setText(const std::string text);
        void setTextAlignment(TextAlignment alignment);

        bool isMouseOver(const sf::Vector2i& mousePos);

        void setBorderColor(const sf::Color &color);
        void setBorderThickness(const float thickness);
        void setBackgroundColor(const sf::Color &color);

        //getPosition
        //setPosition



    protected:
    private:
        float xPos;
        float yPos;
        int width;
        int height;

        sf::Text* text;
        TextAlignment alignment;

        sf::Color borderColor;

        sf::Shape* background;

        bool hoverEnabled;
        bool hovering;

        bool mouseInsideHitbox(const sf::Vector2i& mousePos);
        void setBackgroundAlpha(int alpha);

        virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;
};

#endif // BUTTON_H

#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include "Screen.h"
#include "Button.h"
#include "TextField.h"


class MainScreen : public Screen
{
    public:
        MainScreen();
        virtual ~MainScreen();

        bool isMouseOver(const sf::Vector2i& mousePos);
        int click(const sf::Vector2i& mousePos);

    protected:
    private:
        sf::Font* font;

        sf::Texture* backgroundTexture;
        sf::Sprite* backgroundSprite;

        //float calcBackgroundXScaling();

        sf::Text* gameTitleText;


        Button* joinGameButton;
        Button* hostGameButton;
        Button* settingsButton;
        Button* exitGameButton;

        TextField* textField;



        virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;

};

#endif // MAINSCREEN_H

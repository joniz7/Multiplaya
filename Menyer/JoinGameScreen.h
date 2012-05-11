#ifndef JOINGAMESCREEN_H
#define JOINGAMESCREEN_H

#include "Screen.h"
#include "Button.h"
#include "TextField.h"

class JoinGameScreen : public Screen
{
    public:
        JoinGameScreen();
        virtual ~JoinGameScreen();
    protected:
    private:
        sf::Font* font;
        sf::Shape* background;
        Button* connectButton;
        Button* cancelButton;

        sf::Text* screenTitleText;
        virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;
};

#endif // JOINGAMESCREEN_H

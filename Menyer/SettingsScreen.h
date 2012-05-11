#ifndef SETTINGSSCREEN_H
#define SETTINGSSCREEN_H

#include "Screen.h"

class SettingsScreen : public Screen
{
    public:
        SettingsScreen();
        virtual ~SettingsScreen();

        virtual int run ();
    protected:
    private:
        virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;
};

#endif // SETTINGSSCREEN_H

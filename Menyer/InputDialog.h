#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H

#include "Button.h"
#include "TextField.h"

class InputDialog
{
    public:
        InputDialog();
        virtual ~InputDialog();
    protected:
    private:
        Button* okButton;
        Button* cancelButton;
        TextField* inputField;
        //virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;
};

#endif // INPUTDIALOG_H

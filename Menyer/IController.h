#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <sfml/Graphics.hpp>

class IController
{
    public:
        void handleInput(sf::Event& event) = 0;
    protected:
    private:
};

#endif // CONTROLLER_H

#ifndef HOSTGAMECONTROLLER_H
#define HOSTGAMECONTROLLER_H

#include "IController.h"

class HostGameController : public IController
{
    public:
        HostGameController();
        virtual ~HostGameController();
        void handleInput(sf::Event& event);
    protected:
    private:

};

#endif // HOSTGAMECONTROLLER_H

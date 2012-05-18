#ifndef GLOBAL_H // header guards
#define GLOBAL_H

#include "sfml.h"

// extern tells the compiler this variable is declared elsewhere
extern sf::Mutex worldMutex;
extern sf::Mutex worldDataMutex;
extern sf::Mutex worldViewMutex;

#endif
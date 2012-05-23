//SFML specific headers
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

//Other headers
#include <iostream>
#include <list>

//Game specific headers
#include "app.h"

/**
 * Entry point of application.
 * @returns Application exit code
 */
int main() {
    // Create the application,
	mp::App application;
    // and run it.
    return application.exec();
}

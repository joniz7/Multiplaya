////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
//SFML specific headers
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

//Other headers
#include <iostream>
#include <list>

//Game specific headers
#include "app.h"

////////////////////////////////////////////////////////////
/// Entry point of application
///
/// \return Application exit code
///
////////////////////////////////////////////////////////////

int main()
{
	const int WIDTH = 1280;
	const int HEIGHT = 720;
    // Create the application
	mp::App application(sf::VideoMode(WIDTH, HEIGHT, 32));

	//Do pre-launch stuff

    //Run
    return application.exec();
}

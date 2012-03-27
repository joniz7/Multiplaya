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
#include "sys/app.h"

////////////////////////////////////////////////////////////
/// Entry point of application
///
/// \return Application exit code
///
////////////////////////////////////////////////////////////

int main()
{
	const int WIDTH = 800;
	const int HEIGHT = 600;
    // Create the application
	mp::App application(sf::VideoMode(WIDTH, HEIGHT, 32));

	//Do pre-launch stuff

    //Run
    return application.exec();
}

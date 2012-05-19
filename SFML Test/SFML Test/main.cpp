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
    std::cout << "hej" << std::endl;

    // Create the application
	mp::App application;

    std::cout << "då" << std::endl;

    //Run
    return application.exec();

    std::cout << "re" << std::endl;
}

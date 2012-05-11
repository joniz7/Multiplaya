#include <fstream>
#include <iostream>

#include "Controller.h"
#include "Window.h"


int main()
{

    // create window
    Window window();
    window.run();
    // create controller send reference to window
    Controller controller(&window);
    controller.run();
    // call window run which is a loop

    // call controller run which is a loop

    // create a loop which calls run from here instead, when not threaded atleast

    return EXIT_SUCCESS;
}

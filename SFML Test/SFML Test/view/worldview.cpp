////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
// Class header
#include "worldview.h"

#include <iostream>

////////////////////////////////////////////////////////////
/// World class. Takes care of game physics and logic
////////////////////////////////////////////////////////////

namespace mp
{
	////////////////////////////////////////////////////////////
	// Constructor
	////////////////////////////////////////////////////////////
    WorldView::WorldView()
	{
		std::cout << "WorldView constructor." << std::endl;
	}

	sf::RenderWindow* WorldView::getWindow() {
		std::cout << "getWindow()" << std::endl;
		return window;
	}

	sf::View* WorldView::getView() {
		std::cout << "getView()" << std::endl;
		return view;
	}

	const int WIDTH = 800;
	const int HEIGHT = 600;

	////////////////////////////////////////////////////////////
	// The graphics loop.
	// Fetches info, prints to screen, repeat.
	////////////////////////////////////////////////////////////
	void WorldView::exec() {

		//------------Startup stuff------------
		// Pixel to meter scale. A value of 10 = 10 pixels equals one meter
		sf::VideoMode videoMode(sf::VideoMode(WIDTH, HEIGHT, 32));
		float pixelScale = 1/10.0f;
		// set member variable
		window = new sf::RenderWindow(videoMode, "SFML Test Window");
        sf::Clock clock;
        window->setVerticalSyncEnabled(true);
        window->setFramerateLimit(60);
        sf::RectangleShape background( sf::Vector2f(1600*pixelScale,1200*pixelScale) );
		background.setOrigin(800*pixelScale,600*pixelScale);
		background.setPosition(0,0);
        background.setFillColor( sf::Color(75,75,75) );
        //-------------------------------------


		//----Test stuff----
		sf::RectangleShape ground = sf::RectangleShape( sf::Vector2f(100*pixelScale,5*pixelScale) );
		ground.setFillColor( sf::Color(25,25,25) );
		ground.setOrigin(50*pixelScale,2.5f*pixelScale);
		ground.setPosition(0,-50.0f*pixelScale);

		sf::RectangleShape ground2 = sf::RectangleShape( sf::Vector2f(100*pixelScale,5*pixelScale) );
		ground2.setFillColor( sf::Color(25,25,25) );
		ground2.setOrigin(50*pixelScale,2.5f*pixelScale);
		ground2.setPosition(0,50.0f*pixelScale);
		
		sf::RectangleShape ground3 = sf::RectangleShape( sf::Vector2f(5*pixelScale,100*pixelScale) );
		ground3.setFillColor( sf::Color(25,25,25) );
		ground3.setOrigin(2.5f*pixelScale,50*pixelScale);
		ground3.setPosition(50.0f*pixelScale,0);

		sf::RectangleShape ground4 = sf::RectangleShape( sf::Vector2f(5*pixelScale,100*pixelScale) );
		ground4.setFillColor( sf::Color(25,25,25) );
		ground4.setOrigin(2.5f*pixelScale,50*pixelScale);
		ground4.setPosition(-50.0f*pixelScale,0);
		
		sf::RectangleShape redBox = sf::RectangleShape( sf::Vector2f(2*pixelScale,2*pixelScale) );
		redBox.setOrigin(1*pixelScale,1*pixelScale);
		redBox.setFillColor(sf::Color(255,128,128));
		redBox.setOutlineThickness(0.1f*pixelScale);
		redBox.setOutlineColor(sf::Color::Black);
		
		sf::RectangleShape blueBox = sf::RectangleShape( sf::Vector2f(2*pixelScale,2*pixelScale) );
		blueBox.setOrigin(1*pixelScale,1*pixelScale);
		blueBox.setFillColor(sf::Color(128,128,255));
		blueBox.setOutlineThickness(0.1f*pixelScale);
		blueBox.setOutlineColor(sf::Color::Black);

		sf::RectangleShape bulletVis = sf::RectangleShape( sf::Vector2f(0.5f*pixelScale,1.5f*pixelScale) );
		bulletVis.setOrigin(0.05f*pixelScale,0.25f*pixelScale);
		bulletVis.setFillColor(sf::Color(255,255,255));
		bulletVis.setOutlineThickness(0.1f*pixelScale);
		bulletVis.setOutlineColor(sf::Color::Black);
        //------------------

		//----SFML stuff----
		sf::Vector2f center(0,0);
		sf::Vector2f halfSize(400*pixelScale,300*pixelScale);
		view = new sf::View(center*pixelScale, halfSize*pixelScale);
		// Rotate the view 180 degrees
		view->setRotation(180);
		// Zoom view
		view->zoom( 3.75 );
		// Set view
		window->setView(*view);
		//------------------

		std::cout << "WorldView exec()" << std::endl;

		bool isRunning = true;
		while(isRunning) {

			// Get elapsed time since last frame
            float elapsed = clock.getElapsedTime().asSeconds();
            clock.restart();

/* TODO :)
			// Set redbox
			redBox.setPosition(position.x*pixelScale,position.y*pixelScale);
			redBox.setRotation( angle*180/pi );
			// Set bluebox
			blueBox.setPosition(position.x*pixelScale,position.y*pixelScale);
			blueBox.setRotation( angle*180/pi );
			// set bullet
			bulletVis.setPosition( sf::Vector2f(boolet->getBody()->GetPosition().x*pixelScale,boolet->getBody()->GetPosition().y*pixelScale) );
			bulletVis.setRotation( a * 180/-pi );
*/

            // Clear screen
            window->clear();
            window->draw(background);

            //----------Drawing phase----------
			window->draw(ground);
			window->draw(ground2);
			window->draw(ground3);
			window->draw(ground4);
			window->draw(redBox);
			window->draw(blueBox);
			window->draw(bulletVis);
            //---------------------------------

            // Update the window
            window->display();

		}
	}

	////////////////////////////////////////////////////////////
	// Destructor
	////////////////////////////////////////////////////////////
    WorldView::~WorldView()
    {

    }

}

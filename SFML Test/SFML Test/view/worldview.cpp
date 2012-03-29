////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
// Class header
#include "worldview.h"
#include "../model/worlddata.h"

#include <iostream>

#include "../global.h"

////////////////////////////////////////////////////////////
/// World class. Takes care of game physics and logic
////////////////////////////////////////////////////////////

namespace mp
{
	////////////////////////////////////////////////////////////
	// Constructor
	////////////////////////////////////////////////////////////
    WorldView::WorldView( WorldData* worldData )
	{
		this->worldData = worldData;
	}

	sf::RenderWindow* WorldView::getWindow() {
		std::cout << "getWindow()" << std::endl;
		return window;
	}

	sf::View* WorldView::getView() {
		std::cout << "getView()" << std::endl;
		return view1;
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
		bulletVis.setOrigin(0.25f*pixelScale,0.75f*pixelScale);
		bulletVis.setFillColor(sf::Color(255,255,255));
		bulletVis.setOutlineThickness(0.1f*pixelScale);
		bulletVis.setOutlineColor(sf::Color::Black);
        //------------------

		//----SFML stuff----
		sf::Vector2f center(0,0);
		sf::Vector2f halfSize(400*pixelScale,300*pixelScale);
		view1 = new sf::View(center*pixelScale, halfSize*pixelScale);
		// Rotate the view 180 degrees
		view1->setRotation(180);
		// Zoom view
		view1->zoom( 3.75 );
		// Set view
		window->setView(*view1);
		//------------------

		std::cout << "Initialized render window" << std::endl;

		int counter = 0;

		bool running = true;
        while (running)
        {
            // Get elapsed time since last frame
            float elapsed = clock.getElapsedTime().asSeconds();
            clock.restart();

			if(counter==3)
			{
				int frameFps = 1/elapsed;
				std::cout<<"Rendering fps: "<<frameFps<<std::endl;
				counter = 0;
			}
			else
				counter++;

            // Handle events
            sf::Event Event;
            while (window->pollEvent(Event))
            {
				// Shut down application if user closes window or hits ESC key
                if ( Event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) )
                    window->close();

				// Handle zooming of viewport
				if ( Event.type == sf::Event::MouseWheelMoved )
				{
					if( Event.mouseWheel.delta > 0)
						view1->zoom(0.9f);
					else
						view1->zoom(1.1f);
					window->setView(*view1);
				}
            }

            if( sf::Mouse::isButtonPressed( sf::Mouse::Right ) )
            {
				// Move box to mouse view coordinates
				sf::Vector2f position = window->convertCoords( sf::Mouse::getPosition(*window).x , sf::Mouse::getPosition(*window).y, *view1 ) / pixelScale;
				redBox.setPosition(position);
				/*
				body->SetTransform(b2Vec2(position.x,position.y),0);
				body->SetAwake(true);
				*/
            }
            if( sf::Mouse::isButtonPressed(sf::Mouse::Left) )
            {
				// Move box to mouse view coordinates
				sf::Vector2f position = window->convertCoords( sf::Mouse::getPosition(*window).x,sf::Mouse::getPosition(*window).y, *view1 ) / pixelScale;
				/*
				body2->SetTransform(b2Vec2(position.x,position.y),0);
				body2->SetAwake(true);
				*/
            }

			/*
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				body->ApplyForce( b2Vec2(100,0), body->GetPosition() );
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				body->ApplyForce( b2Vec2(-100,0), body->GetPosition() );
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				body->ApplyForce( b2Vec2(0,100), body->GetPosition() );
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				body->ApplyForce( b2Vec2(0,-100), body->GetPosition() );

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				body->ApplyForce( b2Vec2(0,250), body->GetPosition() );

			// Perform a physics step
			world->Step(timeStep,velocityIterations,positionIterations);
			// Clear physics forces in prep for next step
			world->ClearForces();
			*/

			// Access world data
			worldDataMutex.lock();
			std::vector<b2Body*>* tv = worldData->getBodyVec();
			std::vector<Bullet>* bv = worldData->getBltVec();
			
			if(tv->size() > 0)
			{
				b2Vec2 position = worldData->getBody(0)->GetPosition();
				float32 angle = worldData->getBody(0)->GetAngle();
				redBox.setPosition(position.x*pixelScale,position.y*pixelScale);
				redBox.setRotation( angle*180/pi );
			}

			if(tv->size() > 1)
			{
				b2Vec2 position = worldData->getBody(1)->GetPosition();
				float32 angle = worldData->getBody(1)->GetAngle();
				blueBox.setPosition(position.x*pixelScale,position.y*pixelScale);
				blueBox.setRotation( angle*180/pi );
			}

			if(tv->size() > 0)
			{
				b2Vec2 position = worldData->getBullet(0)->getBody()->GetPosition();
				b2Vec2 v = worldData->getBullet(0)->getBody()->GetLinearVelocity();
				float a = atan(v.x/v.y);
				bulletVis.setPosition(position.x*pixelScale,position.y*pixelScale);
				bulletVis.setRotation( a * 180/-pi );
			}

			/*
			std::cout<<"1"<<std::endl;

			// Get model data
			b2Vec2 position = worldData->getBody(0)->GetPosition();
			float32 angle = worldData->getBody(0)->GetAngle();
			std::cout<<"2"<<std::endl;
			// Set view data
			redBox.setPosition(position.x*pixelScale,position.y*pixelScale);
			redBox.setRotation( angle*180/pi );
			// Get model data
			position = worldData->getBody(1)->GetPosition();
			angle = worldData->getBody(1)->GetAngle();
			// Set view data
			blueBox.setPosition(position.x*pixelScale,position.y*pixelScale);
			blueBox.setRotation( angle*180/pi );

			bulletVis.setPosition( sf::Vector2f(worldData->getBullet(0)->getBody()->GetPosition().x*pixelScale,worldData->getBullet(0)->getBody()->GetPosition().y*pixelScale) );

			b2Vec2 v = worldData->getBullet(0)->getBody()->GetLinearVelocity();
			float a = atan(v.x/v.y);
			bulletVis.setRotation( a * 180/-pi );
			*/
			worldDataMutex.unlock();

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

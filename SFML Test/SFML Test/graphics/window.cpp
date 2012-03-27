////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
//Other headers
#include <string>
#include <cstdlib>
#include <list>

//SFML specific headers
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

//Box2D specific headers
#include <Box2D.h>

//Game specific headers
#include "window.h"

#define pi 3.14159265

////////////////////////////////////////////////////////////
/// Application rendering window
////////////////////////////////////////////////////////////

namespace mp
{
	////////////////////////////////////////////////////////////
	// Constructor
	////////////////////////////////////////////////////////////
    Window::Window(sf::VideoMode mode, std::string title) : RenderWindow(mode, title)
    {

    }

	////////////////////////////////////////////////////////////
	// Destructor
	////////////////////////////////////////////////////////////
    Window::~Window()
    {

    }

	////////////////////////////////////////////////////////////
	// Render window execute function. Runs the game loop
	//
	// \return Application exit code
	////////////////////////////////////////////////////////////
    int Window::exec()
    {

        //------------Startup stuff------------
        sf::Clock clock;
        setVerticalSyncEnabled(true);
        setFramerateLimit(60);
        sf::RectangleShape background( sf::Vector2f(1600,1200) );
		background.setOrigin(800,600);
		background.setPosition(0,0);
        background.setFillColor( sf::Color(75,75,75) );
        //-------------------------------------

        //----Test stuff----
		sf::RectangleShape ground = sf::RectangleShape( sf::Vector2f(100,20) );
		ground.setFillColor( sf::Color(25,25,25) );
		ground.setOrigin(50,10);
		ground.setPosition(0,-10.0f);
		sf::RectangleShape box = sf::RectangleShape( sf::Vector2f(2,2) );
		box.setOrigin(1,1);
		sf::RectangleShape box2 = sf::RectangleShape( sf::Vector2f(2,2) );
		box2.setOrigin(1,1);
		// Pixel to meter scale. A value of 10 = 10 pixels equals one meter
		float pixelScale = 10;
        //------------------

		//----SFML stuff----
		sf::Vector2f center(0,0);
		sf::Vector2f halfSize(400,300);
		sf::View view1(center, halfSize);
		// Rotate the view 180 degrees
		view1.setRotation(180);
		// Zoom view
		view1.zoom( 1/pixelScale );
		// Set view
		setView(view1);
		//------------------

		// Setup the world properties
		bool doSleep = true;
		b2Vec2 gravity(0,-9.8f);
		// Create the world
		b2World* world;
		world = new b2World(gravity);
		world->SetAllowSleeping(doSleep);

		//Define a ground body
		b2BodyDef groundBodyDef;
		groundBodyDef.position.Set(0.0f, -10.0f);
		// Call the body factory which allocates memory for the ground body
		// from a pool and creates the ground box shape (also from a pool).
		// The body is also added to the world.
		b2Body* groundBody = world->CreateBody(&groundBodyDef);
		// Define the ground box shape.
		b2PolygonShape groundBox;
		// The extents are the half-widths of the box.
		groundBox.SetAsBox(50.0f, 10.0f);
		// Add the ground fixture to the ground body.
		groundBody->CreateFixture(&groundBox, 0.0f);

		// Define the dynamic body. We set its position and call the body factory.
		b2BodyDef bodyDef;
		b2BodyDef bodyDef2;
		bodyDef.type = b2_dynamicBody;
		bodyDef2.type = b2_dynamicBody;
		bodyDef.position.Set(0.0f, 4.0f);
		bodyDef2.position.Set(1.0f, 8.0f);
		b2Body* body = world->CreateBody(&bodyDef);
		b2Body* body2 = world->CreateBody(&bodyDef2);
		// Define another box shape for our dynamic body.
		b2PolygonShape dynamicBox;
		dynamicBox.SetAsBox(1.0f, 1.0f);
		// Define the dynamic body fixture.
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &dynamicBox;
		// Set the box density to be non-zero, so it will be dynamic.
		fixtureDef.density = 1.0f;
		// Override the default friction.
		fixtureDef.friction = 0.3f;
		// Set restitution
		fixtureDef.restitution = 0.2f;
		// Add the shape to the body.
		body->CreateFixture(&fixtureDef);
		body2->CreateFixture(&fixtureDef);

		// Prep for simulation
		float32 timeStep = 1.0f / 60.0f;
		int32 velocityIterations = 6;
		int32 positionIterations = 2;

        // Main loop
        bool Running = true;
        while (Running)
        {
            // Get elapsed time since last frame
            float elapsed = clock.getElapsedTime().asSeconds();
            clock.restart();

            // Handle events
            sf::Event Event;
            while (pollEvent(Event))
            {
				// Shut down application if user closes window or hits ESC key
                if ( Event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) )
                    close();
            }

            if( sf::Mouse::isButtonPressed( sf::Mouse::Right ) )
            {
				sf::Vector2f position = convertCoords( sf::Mouse::getPosition().x,sf::Mouse::getPosition().y, view1 );
				body->SetTransform(b2Vec2(position.x,position.y),0);
				body->SetAwake(true);
				/*
				view1.zoom(0.9);
				setView(view1);
				*/
            }
            if( sf::Mouse::isButtonPressed(sf::Mouse::Left) )
            {
				sf::Vector2f position = convertCoords( sf::Mouse::getPosition().x,sf::Mouse::getPosition().y, view1 );
				body2->SetTransform(b2Vec2(position.x,position.y),0);
				body2->SetAwake(true);
				/*
				view1.zoom(1.1);
				setView(view1);
				*/
            }

			// Perform a physics step
			world->Step(timeStep,velocityIterations,positionIterations);
			// Clear physics forces in prep for next step
			world->ClearForces();

			b2Vec2 position = body->GetPosition();
			float32 angle = body->GetAngle();

			box.setPosition(position.x,position.y);
			box.setRotation( angle*180/pi );

			position = body2->GetPosition();
			angle = body2->GetAngle();

			box2.setPosition(position.x,position.y);
			box2.setRotation( angle*180/pi );

            // Clear screen
            clear();
            draw(background);

            //----------Drawing phase----------
			draw(ground);
			draw(box);
			draw(box2);
            //---------------------------------

            // Update the window
            display();

        }
        return EXIT_SUCCESS;
    }
}

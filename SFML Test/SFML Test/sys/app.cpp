////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
// Class header
#include "app.h"

// Other headers
#include <string>
#include <cstdlib>
#include <list>

// SFML specific headers
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// Box2D specific headers
#include <Box2D.h>

// Game specific headers
#include "../game/bullet.h"

#define pi 3.14159265

////////////////////////////////////////////////////////////
/// Application rendering window
////////////////////////////////////////////////////////////

namespace mp
{
	////////////////////////////////////////////////////////////
	// Constructor
	////////////////////////////////////////////////////////////
    App::App(sf::VideoMode mode)
    {
		videoMode = mode;
    }

	////////////////////////////////////////////////////////////
	// Destructor
	////////////////////////////////////////////////////////////
    App::~App()
    {

    }

	////////////////////////////////////////////////////////////
	// Render window execute function. Runs the game loop
	//
	// \return Application exit code
	////////////////////////////////////////////////////////////
    int App::exec()
    {

        //------------Startup stuff------------
		sf::RenderWindow window(videoMode, "SFML Test Window");
        sf::Clock clock;
        window.setVerticalSyncEnabled(true);
        window.setFramerateLimit(60);
        sf::RectangleShape background( sf::Vector2f(1600,1200) );
		background.setOrigin(800,600);
		background.setPosition(0,0);
        background.setFillColor( sf::Color(75,75,75) );
		// Pixel to meter scale. A value of 10 = 10 pixels equals one meter
		float pixelScale = 10;
        //-------------------------------------

        //----Test stuff----
		sf::RectangleShape ground = sf::RectangleShape( sf::Vector2f(100,5) );
		sf::RectangleShape ground2 = sf::RectangleShape( sf::Vector2f(100,5) );
		sf::RectangleShape ground3 = sf::RectangleShape( sf::Vector2f(5,100) );
		sf::RectangleShape ground4 = sf::RectangleShape( sf::Vector2f(5,100) );
		ground.setFillColor( sf::Color(25,25,25) );
		ground2.setFillColor( sf::Color(25,25,25) );
		ground3.setFillColor( sf::Color(25,25,25) );
		ground4.setFillColor( sf::Color(25,25,25) );
		ground.setOrigin(50,2.5f);
		ground2.setOrigin(50,2.5f);
		ground3.setOrigin(2.5f,50);
		ground4.setOrigin(2.5f,50);
		ground.setPosition(0,-50.0f);
		ground2.setPosition(0,50.0f);
		ground3.setPosition(50.0f,0);
		ground4.setPosition(-50.0f,0);

		sf::RectangleShape box = sf::RectangleShape( sf::Vector2f(2,2) );
		box.setOrigin(1,1);
		box.setFillColor(sf::Color(255,128,128));
		box.setOutlineThickness(1/pixelScale);
		box.setOutlineColor(sf::Color::Black);
		sf::RectangleShape box2 = sf::RectangleShape( sf::Vector2f(2,2) );
		box2.setOrigin(1,1);
		box2.setFillColor(sf::Color(128,128,255));
		box2.setOutlineThickness(1/pixelScale);
		box2.setOutlineColor(sf::Color::Black);

		sf::RectangleShape bulletVis = sf::RectangleShape( sf::Vector2f(0.5f,1.5f) );
		bulletVis.setOrigin(0.05f,0.25f);
		bulletVis.setFillColor(sf::Color(255,255,255));
		bulletVis.setOutlineThickness(1/pixelScale);
		bulletVis.setOutlineColor(sf::Color::Black);
        //------------------

		//----SFML stuff----
		sf::Vector2f center(0,0);
		sf::Vector2f halfSize(400,300);
		sf::View view1(center, halfSize);
		// Rotate the view 180 degrees
		view1.setRotation(180);
		// Zoom view
		view1.zoom( 1/(0.25*pixelScale) );
		// Set view
		window.setView(view1);
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
		groundBodyDef.position.Set(0.0f, -50.0f);
		// Call the body factory which allocates memory for the ground body
		// from a pool and creates the ground box shape (also from a pool).
		// The body is also added to the world.
		b2Body* groundBody = world->CreateBody(&groundBodyDef);
		groundBodyDef.position.Set(0.0f, 50.0f);
		b2Body* groundBody2 = world->CreateBody(&groundBodyDef);
		groundBodyDef.position.Set(50.0f, 0);
		b2Body* groundBody3 = world->CreateBody(&groundBodyDef);
		groundBodyDef.position.Set(-50.0f, 0);
		b2Body* groundBody4 = world->CreateBody(&groundBodyDef);

		// Define the ground box shape.
		b2PolygonShape groundBox;
		b2PolygonShape groundBox2;
		// The extents are the half-widths of the box.
		groundBox.SetAsBox(50.0f, 2.5f);
		groundBox2.SetAsBox(2.5f, 50.0f);
		// Add the ground fixture to the ground body.
		groundBody->CreateFixture(&groundBox, 0.0f);
		groundBody2->CreateFixture(&groundBox, 0.0f);
		groundBody3->CreateFixture(&groundBox2, 0.0f);
		groundBody4->CreateFixture(&groundBox2, 0.0f);

		Bullet* boolet = new Bullet(world,b2Vec2(10,10),b2Vec2(-10000,10000));

		// Define the dynamic body. We set its position and call the body factory.
		b2BodyDef bodyDef;
		b2BodyDef bodyDef2;
		bodyDef.type = b2_dynamicBody;
		bodyDef2.type = b2_dynamicBody;
		//bodyDef.fixedRotation = true;
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
		fixtureDef.friction = 0.9f;
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
            while (window.pollEvent(Event))
            {
				// Shut down application if user closes window or hits ESC key
                if ( Event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) )
                    window.close();

				// Handle zooming of viewport
				if ( Event.type == sf::Event::MouseWheelMoved )
				{
					if( Event.mouseWheel.delta > 0)
						view1.zoom(0.9);
					else
						view1.zoom(1.1);
					window.setView(view1);
				}
            }

            if( sf::Mouse::isButtonPressed( sf::Mouse::Right ) )
            {
				// Move box to mouse view coordinates
				sf::Vector2f position = window.convertCoords( sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y, view1 );
				body->SetTransform(b2Vec2(position.x,position.y),0);
				body->SetAwake(true);
            }
            if( sf::Mouse::isButtonPressed(sf::Mouse::Left) )
            {
				// Move box to mouse view coordinates
				sf::Vector2f position = window.convertCoords( sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y, view1 );
				body2->SetTransform(b2Vec2(position.x,position.y),0);
				body2->SetAwake(true);
            }

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				body->ApplyForce( b2Vec2(100,0), body->GetPosition() );
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				body->ApplyForce( b2Vec2(-100,0), body->GetPosition() );
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				body->ApplyForce( b2Vec2(0,100), body->GetPosition() );
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				body->ApplyForce( b2Vec2(0,-100), body->GetPosition() );

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				body->ApplyForce( b2Vec2(0,3050), body->GetPosition() );

			// Perform a physics step
			world->Step(timeStep,velocityIterations,positionIterations);
			// Clear physics forces in prep for next step
			world->ClearForces();

			// Get model data
			b2Vec2 position = body->GetPosition();
			float32 angle = body->GetAngle();
			// Set view data
			box.setPosition(position.x,position.y);
			box.setRotation( angle*180/pi );
			// Get model data
			position = body2->GetPosition();
			angle = body2->GetAngle();
			// Set view data
			box2.setPosition(position.x,position.y);
			box2.setRotation( angle*180/pi );

			bulletVis.setPosition( sf::Vector2f(boolet->getBody()->GetPosition().x,boolet->getBody()->GetPosition().y) );

			b2Vec2 v = boolet->getBody()->GetLinearVelocity();
			float a = atan(v.x/v.y);
			bulletVis.setRotation( a * 180/-pi );

            // Clear screen
            window.clear();
            window.draw(background);

            //----------Drawing phase----------
			window.draw(ground);
			window.draw(ground2);
			window.draw(ground3);
			window.draw(ground4);
			window.draw(box);
			window.draw(box2);
			window.draw(bulletVis);
            //---------------------------------

            // Update the window
            window.display();

        }
        return EXIT_SUCCESS;
    }
}

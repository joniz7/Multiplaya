////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
// Class header
#include "worldview.h"
#include "../model/worlddata.h"

#include <iostream>
#include <sstream>

#include "../global.h"

#include "../services/confighandler.h"

////////////////////////////////////////////////////////////
/// World class. Takes care of game physics and logic
////////////////////////////////////////////////////////////

namespace mp
{
	const float WIDTH = ConfigHandler::getInstance().getInt("res_x");
	const float HEIGHT = ConfigHandler::getInstance().getInt("res_y");

	////////////////////////////////////////////////////////////
	// Constructor
	////////////////////////////////////////////////////////////
    WorldView::WorldView(WorldData* worldData){this->worldData = worldData;}

	////////////////////////////////////////////////////////////
	// Convert int to string. TODO: Should be moved to util file
	// and included instead.
	////////////////////////////////////////////////////////////
	std::string convertInt(int number)
	{
	   std::stringstream ss;//create a stringstream
	   ss << number;//add number to the stream
	   return ss.str();//return a string with the contents of the stream
	}

	////////////////////////////////////////////////////////////
	// The graphics loop.
	// Fetches info, prints to screen, repeat.
	////////////////////////////////////////////////////////////
	void WorldView::exec() {
		//------------Startup stuff------------
		// Set up and initialize render window
		sf::VideoMode videoMode(sf::VideoMode(WIDTH, HEIGHT, 32));
		sf::RenderWindow window(videoMode, "SFML Test Window");
		// Don't display mouse cursor
		window.setMouseCursorVisible(false);
		// Pixel to meter scale. A value of 10 = 10 pixels equals one meter
		float pixelScale = 1/10.0f;
		// Clock for frame time counting
        sf::Clock clock;
		// Set window data
        window.setVerticalSyncEnabled(ConfigHandler::getInstance().getBool("vsync"));
        window.setFramerateLimit(ConfigHandler::getInstance().getInt("fpslimit"));
		// Background stuff
        sf::RectangleShape background( sf::Vector2f(WIDTH*2*pixelScale,HEIGHT*2*pixelScale) );
		background.setOrigin(WIDTH/2*pixelScale,HEIGHT/2*pixelScale);
		background.setPosition(0,0);
        background.setFillColor( sf::Color(75,75,75) );
        //-------------------------------------

		//----Test stuff----
		if(!hudTex.loadFromFile("resources/hud.png"))
			std::cout<<"Failed to load texture: hud.png"<<std::endl;
		hudSpr.setTexture(hudTex);
		hudSpr.setScale(WIDTH/1920,HEIGHT/1080);

		sf::Texture dotTex;
		sf::Sprite dotSpr;
		if(!dotTex.loadFromFile("resources/reddot.png"))
			std::cout<<"Failed to load texture: reddot.png"<<std::endl;
		dotSpr.setTexture(dotTex);
		dotSpr.setOrigin(32,32);
		dotSpr.setScale(0.5,0.5);

		sf::Font fontGothic;
		fontGothic.loadFromFile("resources/gothic.ttf");

		sf::Text renderFpsTxt("Render fps: 00");
		sf::Text logicFpsTxt("Logic fps:  00");
		renderFpsTxt.setFont(fontGothic);
		logicFpsTxt.setFont(fontGothic);
		renderFpsTxt.setCharacterSize(25);
		logicFpsTxt.setCharacterSize(25);
		renderFpsTxt.setStyle(sf::Text::Regular);
		logicFpsTxt.setStyle(sf::Text::Regular);
		renderFpsTxt.setPosition(8, 0);
		logicFpsTxt.setPosition(8, 30);

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
		
		sf::RectangleShape redBox = sf::RectangleShape( sf::Vector2f(2*pixelScale,4*pixelScale) );
		redBox.setOrigin(1*pixelScale,2*pixelScale);
		redBox.setFillColor(sf::Color(255,128,128));
		redBox.setOutlineThickness(0.1f*pixelScale);
		redBox.setOutlineColor(sf::Color::Black);
		
		sf::RectangleShape blueBox = sf::RectangleShape( sf::Vector2f(2*pixelScale,4*pixelScale) );
		blueBox.setOrigin(1*pixelScale,2*pixelScale);
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
		sf::Vector2f halfSize(WIDTH/2*pixelScale,HEIGHT/2*pixelScale);
		view1 = new sf::View(center*pixelScale, halfSize*pixelScale);
		// Rotate the view 180 degrees
		view1->setRotation(180);
		// Zoom view
		//view1->zoom( 3.75 );
		view1->zoom( 1.5 );
		// Set view
		window.setView(*view1);
		//------------------

		std::cout<<"Render window initialized!"<<std::endl;

		int counter = 0;

		sf::Vector2f mousePos(0,0);
		sf::Vector2i mousePosWindow(0,0);
		sf::Vector2f mousePosOld(0,0);
		sf::Vector2f mouseSpeed(0,0);

		bool fixedRotToggle = false;
		bool released = true;

		bool running = true;
        while (running)
        {
			mousePos = window.convertCoords( sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y, *view1 ) / pixelScale;
			mousePosWindow = sf::Mouse::getPosition(window);
			mouseSpeed = (mousePos - mousePosOld)/pixelScale;
            // Get elapsed time since last frame
            float elapsed = clock.getElapsedTime().asSeconds();
            clock.restart();

			// Only display fps every tenth frame (easier to read)
			if(counter==10)
			{
				int renderFps = (int)(1/elapsed);
				worldDataMutex.lock();
				int logicFps = worldData->getLogicFps();
				std::string a = convertInt(renderFps);
				std::string b = convertInt(logicFps);
				//renderFpsTxt.setString(elapsed);
				renderFpsTxt.setString("Render fps: "+a);
				logicFpsTxt.setString("Logic fps:  "+b);
				worldDataMutex.unlock();
				counter = 0;
			}
			else
				counter++;

			/*
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
						view1->zoom(0.9f);
					else
						view1->zoom(1.1f);
					window.setView(*view1);
				}
            }
			*/

			// Right mouse button is down
            if( sf::Mouse::isButtonPressed( sf::Mouse::Right ) )
            {
				
            }

			// Left mouse button is down
            if( sf::Mouse::isButtonPressed(sf::Mouse::Left) )
            {
				// Move box to mouse view coordinates
				worldDataMutex.lock();
				worldData->getBody(1)->SetTransform(b2Vec2(mousePos.x,mousePos.y),0);
				worldData->getBody(1)->SetAwake(true);
				worldData->getBody(1)->SetLinearVelocity(b2Vec2(mouseSpeed.x,mouseSpeed.y));
				worldDataMutex.unlock();

				/*
				body2->SetTransform(b2Vec2(position.x,position.y),0);
				body2->SetAwake(true);
				*/
            }
			
			// Handle box movement. To be moved to Character class
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)||sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				if(worldData->getBody(0)->GetLinearVelocity().x < 10)
				worldData->getBody(0)->ApplyLinearImpulse( b2Vec2(5,0), worldData->getBody(0)->GetPosition() );
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)||sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				if(worldData->getBody(0)->GetLinearVelocity().x > -10)
					worldData->getBody(0)->ApplyLinearImpulse( b2Vec2(-5,0), worldData->getBody(0)->GetPosition() );
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)||sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				if(worldData->getBody(0)->GetLinearVelocity().y < 10)
					worldData->getBody(0)->ApplyLinearImpulse( b2Vec2(0,5), worldData->getBody(0)->GetPosition() );
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)||sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				if(worldData->getBody(0)->GetLinearVelocity().y > -10)
					worldData->getBody(0)->ApplyLinearImpulse( b2Vec2(0,-5), worldData->getBody(0)->GetPosition() );
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				if(released)
				{
					worldData->getBody(0)->ApplyLinearImpulse( b2Vec2(0,125), worldData->getBody(0)->GetPosition() );

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)||sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
						worldData->getBody(0)->ApplyLinearImpulse( b2Vec2(75,0), worldData->getBody(0)->GetPosition() );
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)||sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
						worldData->getBody(0)->ApplyLinearImpulse( b2Vec2(-75,0), worldData->getBody(0)->GetPosition() );

					released = false;
				}
			}
			else
				released = true;
			

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

				// Higher value means more focus on character
				//int cameraBias = 10;

				float x = (((position.x + mousePos.x)/2+position.x)/2+position.x)/2;
				float y = (((position.y + mousePos.y)/2+position.y)/2+position.y)/2;

				view1->setCenter(x*pixelScale,y*pixelScale);
				window.setView(*view1);

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

			dotSpr.setPosition(mousePosWindow.x,mousePosWindow.y);

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

			window.setView(*view1);

            // Clear screen
            window.clear();
            window.draw(background);

            //----------World Rendering phase----------
			window.draw(ground);
			window.draw(ground2);
			window.draw(ground3);
			window.draw(ground4);
			window.draw(redBox);
			window.draw(blueBox);
			window.draw(bulletVis);
            //-----------------------------------------

			//------------UI Rendering phase-----------
			window.setView(window.getDefaultView());
			window.draw(dotSpr);
			window.draw(hudSpr);
			window.draw(renderFpsTxt);
			window.draw(logicFpsTxt);
			//-----------------------------------------

            // Update the window
            window.display();

			mousePosOld = mousePos;

        }
	}

	////////////////////////////////////////////////////////////
	// Destructor
	////////////////////////////////////////////////////////////
    WorldView::~WorldView()
    {

    }

}

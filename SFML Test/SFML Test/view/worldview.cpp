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

#include "animatedsprite.h"

////////////////////////////////////////////////////////////
/// World class. Takes care of game physics and logic
////////////////////////////////////////////////////////////

namespace mp
{
	const float WIDTH = ConfigHandler::instance().getInt("r_width");
	const float HEIGHT = ConfigHandler::instance().getInt("r_height");

	////////////////////////////////////////////////////////////
	// Constructor
	////////////////////////////////////////////////////////////
    WorldView::WorldView(WorldData* worldData){this->worldData = worldData;}

	////////////////////////////////////////////////////////////
	// Safely convert int to string. TODO: Should be moved to
	// util class and included instead.
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
		float pixelScale = 1 / 10.0f;
		// Clock for frame time counting
        sf::Clock clock;
		// Set window data
        window.setVerticalSyncEnabled(ConfigHandler::instance().getBool("r_vsync"));
        window.setFramerateLimit(ConfigHandler::instance().getInt("r_fpslimit"));
		// Background stuff
        sf::RectangleShape background( sf::Vector2f(WIDTH * 2 * pixelScale, HEIGHT * 2 * pixelScale) );
		background.setOrigin(WIDTH / 2 * pixelScale, HEIGHT / 2 * pixelScale);
		background.setPosition(0,0);
        background.setFillColor( sf::Color(30, 30, 30) );
        //-------------------------------------

		//----Test stuff----
		if(!hudTex.loadFromFile("resources/hud.png"))
			std::cout << "Failed to load texture: hud.png" << std::endl;
		hudSpr.setTexture(hudTex);
		hudSpr.setScale(WIDTH / 1920, HEIGHT / 1080);


		sf::Texture lightTex;
		lightTex.loadFromFile("resources/light.png");
		sf::Sprite lightSpr;
		lightSpr.setTexture(lightTex);
		lightSpr.setOrigin(256,256);
		lightSpr.setScale(pixelScale*0.1,pixelScale*0.1);
		lightSpr.setPosition(0,0);
		lightSpr.setColor(sf::Color(255,150,125,75));

		sf::Texture frameTexture;
		frameTexture.loadFromFile("resources/test/testsprite.png");

		AnimatedSprite testSpr(&frameTexture,sf::Vector2i(8,1));
		std::vector<sf::Vector2i> sequence;

		sequence.push_back(sf::Vector2i(2,1));
		sequence.push_back(sf::Vector2i(3,1));
		sequence.push_back(sf::Vector2i(4,1));
		sequence.push_back(sf::Vector2i(5,1));
		sequence.push_back(sf::Vector2i(6,1));
		sequence.push_back(sf::Vector2i(7,1));

		testSpr.addAnimation("walk",9,sequence);

		sequence.clear();
		sequence.push_back(sf::Vector2i(1,1));

		bool facingRight = true;

		testSpr.addAnimation("idle",9,sequence);

		testSpr.rotate(180);
		testSpr.setPosition(0,0);
		testSpr.scale(0.0016,0.0016);
		testSpr.playAnimation("idle");

		sf::Texture dotTex;
		sf::Sprite dotSpr;
		if(!dotTex.loadFromFile("resources/reddot.png"))
			std::cout << "Failed to load texture: reddot.png" << std::endl;
		dotSpr.setTexture(dotTex);
		dotSpr.setOrigin(32, 32);
		dotSpr.setScale(0.5, 0.5);

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

		sf::Color c(10, 10, 10);

		sf::RectangleShape ground = sf::RectangleShape( sf::Vector2f(100 * pixelScale, 5 * pixelScale) );
		ground.setFillColor( c );
		ground.setOrigin(50 * pixelScale, 2.5f * pixelScale);
		ground.setPosition(0, -50.0f * pixelScale);

		sf::RectangleShape ground2 = sf::RectangleShape( sf::Vector2f(100 * pixelScale, 5 * pixelScale) );
		ground2.setFillColor( c );
		ground2.setOrigin(50 * pixelScale, 2.5f * pixelScale);
		ground2.setPosition(0, 50.0f * pixelScale);
		
		sf::RectangleShape ground3 = sf::RectangleShape( sf::Vector2f(5 * pixelScale, 100 * pixelScale) );
		ground3.setFillColor( c );
		ground3.setOrigin(2.5f * pixelScale, 50 * pixelScale);
		ground3.setPosition(50.0f * pixelScale, 0);

		sf::RectangleShape ground4 = sf::RectangleShape( sf::Vector2f(5 * pixelScale, 100 * pixelScale) );
		ground4.setFillColor( c );
		ground4.setOrigin(2.5f * pixelScale, 50 * pixelScale);
		ground4.setPosition(-50.0f * pixelScale, 0);
		
		sf::RectangleShape redBox = sf::RectangleShape( sf::Vector2f(2 * pixelScale, 4 * pixelScale) );
		redBox.setOrigin( 1 * pixelScale, 2 * pixelScale);
		redBox.setFillColor(sf::Color(255, 128, 128));
		redBox.setOutlineThickness(0.1f * pixelScale);
		redBox.setOutlineColor(sf::Color::Black);
		
		sf::RectangleShape blueBox = sf::RectangleShape( sf::Vector2f( 2 * pixelScale, 4 * pixelScale) );
		blueBox.setOrigin(1 * pixelScale, 2 * pixelScale);
		blueBox.setFillColor(sf::Color(128, 128, 255));
		blueBox.setOutlineThickness(0.1f * pixelScale);
		blueBox.setOutlineColor(sf::Color::Black);

		sf::RectangleShape bulletVis = sf::RectangleShape( sf::Vector2f(0.5f * pixelScale, 1.5f * pixelScale) );
		bulletVis.setOrigin(0.25f * pixelScale, 0.75f * pixelScale);
		bulletVis.setFillColor(sf::Color(255, 255, 255));
		bulletVis.setOutlineThickness(0.1f * pixelScale);
		bulletVis.setOutlineColor(sf::Color::Black);
        //------------------

		//----SFML stuff----
		sf::Vector2f center(0,0);
		sf::Vector2f halfSize(WIDTH / 2 * pixelScale, HEIGHT / 2 *pixelScale);
		worldView = new sf::View(center * pixelScale, halfSize * pixelScale);
		// Rotate the view 180 degrees
		worldView->setRotation(180);
		// Zoom view
		//worldView->zoom( 3.75 );
		worldView->zoom( 1.5 );
		// Set view
		window.setView(*worldView);
		//------------------

		std::cout << "Render window initialized!" << std::endl;

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
			mousePos = window.convertCoords( sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y, *worldView ) / pixelScale;
			mousePosWindow = sf::Mouse::getPosition(window);
			mouseSpeed = (mousePos - mousePosOld) / pixelScale;
            // Get elapsed time since last frame
            float elapsed = clock.getElapsedTime().asSeconds();
            clock.restart();

			// Only display fps every tenth frame (easier to read)
			if(counter == 10)
			{
				int renderFps = (int)(1 / elapsed);
				worldDataMutex.lock();
				int logicFps = worldData->getLogicFps();
				std::string a = convertInt(renderFps);
				std::string b = convertInt(logicFps);
				//renderFpsTxt.setString(elapsed);
				renderFpsTxt.setString("Render fps: " + a);
				logicFpsTxt.setString("Logic fps:  " + b);
				worldDataMutex.unlock();
				counter = 0;
			}
			else
				counter++;

			
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
						worldView->zoom(0.9f);
					else
						worldView->zoom(1.1f);
					window.setView(*worldView);
				}
            }
			

			// Right mouse button is down
            if( sf::Mouse::isButtonPressed( sf::Mouse::Right ) )
            {
				
            }

			// Left mouse button is down
            if( sf::Mouse::isButtonPressed(sf::Mouse::Left) )
            {
				// Move box to mouse view coordinates
				worldDataMutex.lock();
				worldData->getBody(1)->SetTransform(b2Vec2(mousePos.x, mousePos.y), 0);
				worldData->getBody(1)->SetAwake(true);
				worldData->getBody(1)->SetLinearVelocity(b2Vec2(mouseSpeed.x, mouseSpeed.y));
				worldDataMutex.unlock();
            }
			// Handle box movement. To be moved to Character class
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)||sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				if(worldData->getBody(0)->GetLinearVelocity().x < 7)
				worldData->getBody(0)->ApplyLinearImpulse( b2Vec2(5,0), worldData->getBody(0)->GetPosition() );

				if(facingRight)
				{
					testSpr.scale(-1,1);
					facingRight = false;
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)||sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				if(worldData->getBody(0)->GetLinearVelocity().x > -7)
					worldData->getBody(0)->ApplyLinearImpulse( b2Vec2(-5,0), worldData->getBody(0)->GetPosition() );
				if(!facingRight)
				{
					testSpr.scale(-1,1);
					facingRight = true;
				}
			}
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
					worldData->getBody(0)->ApplyLinearImpulse( b2Vec2(0,75), worldData->getBody(0)->GetPosition() );

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)||sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
						worldData->getBody(0)->ApplyLinearImpulse( b2Vec2(40,0), worldData->getBody(0)->GetPosition() );
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)||sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
						worldData->getBody(0)->ApplyLinearImpulse( b2Vec2(-40,0), worldData->getBody(0)->GetPosition() );

					released = false;
				}
			}
			else
				released = true;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)||sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				testSpr.playAnimation("walk");
			else
				testSpr.playAnimation("idle");

			// Access world data
			worldDataMutex.lock();
			std::vector<b2Body*>* tv = worldData->getBodyVec();
			std::vector<Bullet>* bv = worldData->getBltVec();
			
			if(tv->size() > 0)
			{
				// Calculate camera position (somehwere between character and mouse)
				b2Vec2 position = worldData->getBody(0)->GetPosition();
				float32 angle = worldData->getBody(0)->GetAngle();
				testSpr.setPosition(position.x*pixelScale,position.y*pixelScale);
				redBox.setRotation( angle*180/pi );

				float x = (((position.x + mousePos.x)/2+position.x)/2+position.x)/2;
				float y = (((position.y + mousePos.y)/2+position.y)/2+position.y)/2;

				worldView->setCenter(x*pixelScale,y*pixelScale);
				window.setView(*worldView);

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

			lightSpr.setPosition(mousePos.x*pixelScale, mousePos.y*pixelScale);

			// Set sight position
			dotSpr.setPosition(mousePosWindow.x,mousePosWindow.y);
			// Unlock world data mutex
			worldDataMutex.unlock();
			// Set world view so we can render the world in world coordinates
			window.setView(*worldView);
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
			testSpr.update(elapsed);
			window.draw(testSpr);
			window.draw(lightSpr,sf::BlendAdd);
            //-----------------------------------------
			//------------UI Rendering phase-----------
			// Set default view so we can render the ui in window coordinates
			window.setView(window.getDefaultView());
			window.draw(dotSpr);
			// Draw hud
			if(ConfigHandler::instance().getBool("r_drawhud"))
			{
				window.draw(hudSpr);
			}
			// Draw debug stuff
			if(ConfigHandler::instance().getBool("s_debugmode"))
			{
				window.draw(renderFpsTxt);
				window.draw(logicFpsTxt);
			}
			//-----------------------------------------
            // Update the window
            window.display();
			// Save mouse position for next frame
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

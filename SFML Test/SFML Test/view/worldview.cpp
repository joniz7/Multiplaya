////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
// Class header
#include "worldview.h"
#include "../model/worlddata.h"

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
    WorldView::WorldView(WorldData* worldData)
	{
		this->worldData = worldData;
		this->pixelScale = 1 / 10.0f;
	}

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
	
	void WorldView::notify(std::string e, void* object)
	{
		if (e == "bulletAdded") 
		{
			Bullet* bullet = ( Bullet* )object;
			addBullet(bullet);
		}
		else if (e == "bulletDeleted")
		{
			int i = ( int )object;
			deleteBullet(i);
		}
	}

	void WorldView::addBullet(Bullet* bullet)
	{
		worldViewMutex.lock();
		bullets.push_back(  new BulletView( bullet ) );
		worldViewMutex.unlock();
	}
	
	// delete bullet at index i 
	void WorldView::deleteBullet(int i)
	{
		worldViewMutex.lock();

		BulletView* bullet = (BulletView*) bullets.at(i);
		bullets.erase(bullets.begin() + i );
		delete bullet;

		worldViewMutex.unlock();
	}
	
	////////////////////////////////////////////////////////////
	// The graphics loop.
	// Fetches info, prints to screen, repeat.
	////////////////////////////////////////////////////////////
	void WorldView::exec() {

		// Initialize the window.
		initialize();

		//----Test stuff----
		if(!hudTex.loadFromFile("resources/hud.png"))
			std::cout << "Failed to load texture: hud.png" << std::endl;
		hudSpr.setTexture(hudTex);
		hudSpr.setScale(WIDTH / 1920, HEIGHT / 1080);

		sf::Texture lightTex;
		lightTex.loadFromFile("resources/light.png");
		lightSpr = new sf::Sprite();
		lightSpr->setTexture(lightTex);
		lightSpr->setOrigin(256, 256);
		lightSpr->setScale(pixelScale * 0.1, pixelScale * 0.1);
		lightSpr->setPosition(0,0);
		lightSpr->setColor(sf::Color(255, 150, 125, 75));

		sf::Texture frameTexture;
		frameTexture.loadFromFile("resources/test/testsprite.png");

		AnimatedSprite testSpr(&frameTexture,sf::Vector2i(8, 1));
		std::vector<sf::Vector2i> sequence;

		sequence.push_back(sf::Vector2i(2, 1));
		sequence.push_back(sf::Vector2i(3, 1));
		sequence.push_back(sf::Vector2i(4, 1));
		sequence.push_back(sf::Vector2i(5, 1));
		sequence.push_back(sf::Vector2i(6, 1));
		sequence.push_back(sf::Vector2i(7, 1));

		testSpr.addAnimation("walk", 9, true, sequence);

		sequence.clear();
		sequence.push_back(sf::Vector2i(1, 1));

		bool facingRight = true;

		testSpr.addAnimation("idle", 9, true, sequence);

		testSpr.rotate(180);
		testSpr.setPosition(0,0);
		testSpr.scale(0.0016f, 0.0016f);
		testSpr.playAnimation("idle");

		sf::Texture dotTex;
		dotSpr = new sf::Sprite();
		if(!dotTex.loadFromFile("resources/reddot.png"))
			std::cout << "Failed to load texture: reddot.png" << std::endl;
		dotSpr->setTexture(dotTex);
		dotSpr->setOrigin(32, 32);
		dotSpr->setScale(0.5, 0.5);


		//instantiate map graphics
		constructMapGraphics();

        //------------------

		characters.push_back( new CharacterView(worldData->getPlayer()->getCharacter(), &testSpr));
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
		window->setView(*worldView);
		//------------------

		std::cout << "Render window initialized!" << std::endl;

		mousePos = new sf::Vector2f(0,0);
		mousePosWindow = new sf::Vector2i(0,0);
		sf::Vector2f mousePosOld(0,0);
		mouseSpeed = new sf::Vector2f(0,0);

		bool fixedRotToggle = false;
		bool released = true;

		bool running = true;
		int counter = 0;
        while (running)
        {
			*mousePos = window->convertCoords( sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y, *worldView ) / pixelScale;
			*mousePosWindow = sf::Mouse::getPosition(*window);
			*mouseSpeed = (*mousePos - mousePosOld) / pixelScale;
            // Get elapsed time since last frame
            float elapsed = clock.getElapsedTime().asSeconds();
            clock.restart();


			// Only display fps every tenth frame (easier to read)
			
			if(counter == 10)
			{
				int renderFps = (int)(1 / elapsed);
				worldDataMutex.lock();
				int logicFps = worldData->getLogicFps();
				
				std::string renderFpsString = convertInt(renderFps);
				renderFpsTxt->setString("Render fps: " + renderFpsString);
				
				std::string logicFpsString = convertInt(logicFps);
				logicFpsTxt->setString("Logic fps:  " + logicFpsString);

				worldData->setMousePosition(mousePos);

				worldDataMutex.unlock();
				counter = 0;
			}
			else
			{
				counter++;
			}

			
            // Handle events
			handleEvents();

			// Access world data
			worldDataMutex.lock();

			std::vector<Character*>* tv = worldData->getCharacters();
					
			if(tv->size() > 0)
			{
				calculateCam();

				b2Vec2 position = worldData->getCharacter(0)->getBody()->GetPosition();
				float32 angle = worldData->getCharacter(0)->getBody()->GetAngle();
				blueBox->setPosition(position.x * pixelScale,position.y*pixelScale);
				blueBox->setRotation( angle * 180 / pi );
			}

			testSpr.update(elapsed);

			updatePositions();

			// Unlock world data mutex
			worldDataMutex.unlock();
			// Set world view so we can render the world in world coordinates
			window->setView(*worldView);
            // Clear screen
            window->clear();
            
            // Render World.
			drawWorld();

			// Render UI.
			drawUI();

            // Update the window
            window->display();
			// Save mouse position for next frame
			mousePosOld = *mousePos;
        }
	}

	//////////////////////////////
	// Initialize everything.
	// Change SFML settings, etc.
	//////////////////////////////
	void WorldView::initialize() {
		// Set up and initialize render window
		sf::VideoMode videoMode(sf::VideoMode(WIDTH, HEIGHT, 32));
		window = new sf::RenderWindow(videoMode, "SFML Test Window");
		
		// Don't display mouse cursor
		window->setMouseCursorVisible(false);
		
		// Set window data
        window->setVerticalSyncEnabled(ConfigHandler::instance().getBool("r_vsync"));
        window->setFramerateLimit(ConfigHandler::instance().getInt("r_fpslimit"));
		
		// Background stuff
		background = new sf::RectangleShape( sf::Vector2f(WIDTH * 2 * pixelScale, HEIGHT * 2 * pixelScale) );
		background->setOrigin(WIDTH / 2 * pixelScale, HEIGHT / 2 * pixelScale);
		background->setPosition(0, 0);
        background->setFillColor( sf::Color(30, 30, 30) );

		// Load font file.
		fontGothic = new sf::Font();
		fontGothic->loadFromFile("resources/gothic.ttf");
		
		// Setup fps labels.
		renderFpsTxt = new sf::Text("Render fps: 00");
		logicFpsTxt = new sf::Text("Logic fps: 00");

		renderFpsTxt->setFont(*fontGothic);
		renderFpsTxt->setCharacterSize(25);
		renderFpsTxt->setStyle(sf::Text::Regular);
		renderFpsTxt->setPosition(8, 0);

		logicFpsTxt->setFont(*fontGothic);
		logicFpsTxt->setCharacterSize(25);
		logicFpsTxt->setStyle(sf::Text::Regular);
		logicFpsTxt->setPosition(8, 30);
	}

	void WorldView::handleEvents()
	{
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
					worldView->zoom(0.9f);
				else
					worldView->zoom(1.1f);
				window->setView(*worldView);
			}
        }
			
		// Left mouse button is down
		if( sf::Mouse::isButtonPressed(sf::Mouse::Left) )
		{
			// Move box to mouse view coordinates
			worldDataMutex.lock();
			worldData->getCharacter(0)->getBody()->SetTransform(b2Vec2(mousePos->x, mousePos->y), 0);
			worldData->getCharacter(0)->getBody()->SetAwake(true);
			worldData->getCharacter(0)->getBody()->SetLinearVelocity(b2Vec2(mouseSpeed->x, mouseSpeed->y));
			worldDataMutex.unlock();
		}
	}

	void WorldView::constructMapGraphics()
	{
		sf::Color c(10, 10, 10);

		ground = new sf::RectangleShape( sf::Vector2f(100 * pixelScale, 5 * pixelScale) );
		ground->setFillColor( c );
		ground->setOrigin(50 * pixelScale, 2.5f * pixelScale);
		ground->setPosition(0, -50.0f * pixelScale);

		ground2 = new sf::RectangleShape( sf::Vector2f(100 * pixelScale, 5 * pixelScale) );
		ground2->setFillColor( c );
		ground2->setOrigin(50 * pixelScale, 2.5f * pixelScale);
		ground2->setPosition(0, 50.0f * pixelScale);
		
		ground3 = new sf::RectangleShape( sf::Vector2f(5 * pixelScale, 100 * pixelScale) );
		ground3->setFillColor( c );
		ground3->setOrigin(2.5f * pixelScale, 50 * pixelScale);
		ground3->setPosition(50.0f * pixelScale, 0);

		ground4 = new sf::RectangleShape( sf::Vector2f(5 * pixelScale, 100 * pixelScale) );
		ground4->setFillColor( c );
		ground4->setOrigin(2.5f * pixelScale, 50 * pixelScale);
		ground4->setPosition(-50.0f * pixelScale, 0);
		
		blueBox = new sf::RectangleShape( sf::Vector2f( 2 * pixelScale, 4 * pixelScale) );
		blueBox->setOrigin(1 * pixelScale, 2 * pixelScale);
		blueBox->setFillColor(sf::Color(128, 128, 255));
		blueBox->setOutlineThickness(0.1f * pixelScale);
		blueBox->setOutlineColor(sf::Color::Black);
	}

	void WorldView::updatePositions()
	{
		// Set sight position
		dotSpr->setPosition(mousePosWindow->x, mousePosWindow->y);
		lightSpr->setPosition(mousePos->x * pixelScale, mousePos->y * pixelScale);

		updateBulletsPos();
		updateCharactersPos();

	}

	void WorldView::updateBulletsPos()
	{
		worldViewMutex.lock();
		updateVectorPos(bullets);
		worldViewMutex.unlock();
	}

	void WorldView::updateCharactersPos()
	{
		worldViewMutex.lock();
		updateVectorPos(characters);
		worldViewMutex.unlock();
	}

	// better name
	void WorldView::drawVector(std::vector<GameObjectView*>& vector)
	{
		std::vector<GameObjectView*>::iterator it;
		for ( it = vector.begin() ; it < vector.end(); it++ )
			window->draw(**it);
	}

	void WorldView::drawWorld()
	{
		drawEnvironment();
		drawCharacters();
		drawBullets();
		// Draw light.
		window->draw(*lightSpr, sf::BlendAdd);
	}


	void WorldView::drawEnvironment()
	{
		window->draw(*background);
		window->draw(*ground);
		window->draw(*ground2);
		window->draw(*ground3);
		window->draw(*ground4);
	}

	void WorldView::drawBullets()
	{
		worldViewMutex.lock();		
		drawVector(bullets);
		worldViewMutex.unlock();
	}
	
	void WorldView::drawCharacters()
	{
		window->draw(*blueBox);

		drawVector(characters);

	}

			// better name maybe
	void WorldView::updateVectorPos(std::vector<GameObjectView*>& vector)
	{
		std::vector<GameObjectView*>::iterator it;
		for ( it = vector.begin() ; it < vector.end(); it++ )
			(*it)->updatePosition();
	}

	void WorldView::drawUI()
	{
		// Set default view so we can render the ui in window coordinates
		window->setView(window->getDefaultView());
		window->draw(*dotSpr);
		// Draw hud
		if(ConfigHandler::instance().getBool("r_drawhud"))
		{
			window->draw(hudSpr);
		}
		// Draw debug labels
		if(ConfigHandler::instance().getBool("s_debugmode"))
		{
			// TODO Access violation. They're initialized in initialize(), what's the deal?
			window->draw(*renderFpsTxt);
			window->draw(*logicFpsTxt);
		}
	}

	void WorldView::calculateCam() 
	{
		// Calculate camera position (somehwere between character and mouse)
		b2Vec2 position = worldData->getPlayer()->getCharacter()->getBody()->GetPosition();
		float32 angle = worldData->getPlayer()->getCharacter()->getBody()->GetAngle();
		//testSpr.setPosition(position.x*pixelScale,position.y*pixelScale);
		
		//redBox.setRotation( angle*180/pi );
		float x = (((position.x + mousePos->x) / 2 + position.x) / 2 + position.x) / 2;
		float y = (((position.y + mousePos->y) / 2 + position.y) / 2 + position.y) / 2;

		worldView->setCenter(x * pixelScale, y * pixelScale);
		window->setView(*worldView);
	}

	////////////////////////////////////////////////////////////
	// Destructor
	////////////////////////////////////////////////////////////
    WorldView::~WorldView()
    {

    }

}



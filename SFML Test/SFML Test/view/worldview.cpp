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
	////////////////////////////////////////////////////////////
	// Constructor
	////////////////////////////////////////////////////////////
	WorldView::WorldView(WorldData* worldData, sf::RenderWindow* window)
	{
		this->worldData = worldData;
		this->window = window;
		this->pixelScale = 1 / 10.0f;
		counter = 0;
		elapsed = 0;

		layerHandler = new LayerHandler();
		characterXPos = 0;
		initialize();
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

	void WorldView::notify(Event e, void* object)
	{
		// could change to switch case
		if (e == BULLET_ADDED)
		{
			Bullet* bullet = ( Bullet* )object;
			addBullet(bullet);
		}
		else if (e == BULLET_DELETED)
		{
			int i = ( intptr_t )object;
			deleteBullet(i);
		}
		else if (e == CHARACTER_ADDED)
		{
			Character* character = (Character*)object;
			addCharacter(character);
		}
	}

	void WorldView::addBullet(Bullet* bullet)
	{
		//worldViewMutex.lock();
		bullets.push_back(  new BulletView( bullet ) );
		//worldViewMutex.unlock();
	}

	// delete bullet at index i
	void WorldView::deleteBullet(int i)
	{
		//worldViewMutex.lock();

		BulletView* bullet = (BulletView*) bullets.at(i);
		bullets.erase(bullets.begin() + i );
		delete bullet;

		//worldViewMutex.unlock();
	}

	/*void WorldView::characterMoved(float moved)
	{
		layerHandler->update(moved);
	}*/

	void WorldView::addCharacter(Character* character)
	{
		characters.push_back( new CharacterView( character ) );
	}

	/////////////////////////////////
	/// Changes the zoom of the camera.
	/// \param zoomFactor - how much we should zoom.
	/////////////////////////////////
	void WorldView::zoom(float zoomFactor) {
		camera->zoom(zoomFactor);
	}

	/////////////////////////////////
	/// Zooms the camera in, if we're
	/// not already at our maximum zoomed-in level.
	/////////////////////////////////
	void WorldView::zoomIn() {
		std::cout << "zooming in." << std::endl;
		if (zoomLevel < zoomLevelMax) {
			camera->zoom(1/1.1);
			zoomLevel++;
		}
	}

	/////////////////////////////////
	/// Zooms the camera out, unless we're at
	/// our maximum zoomed-out level (where we started).
	/////////////////////////////////
	void WorldView::zoomOut() {
		if (zoomLevel > 0) {
			camera->zoom(1.1f);
			zoomLevel--;
		}
	}

	void WorldView::tempLoop()
	{
			// Fetch mouse-related things.
			*mousePosWindow = sf::Mouse::getPosition(*window);
			*mousePos = window->convertCoords( sf::Vector2i(mousePosWindow->x, mousePosWindow->y), *camera ) / pixelScale;

			*mouseSpeed = (*mousePos - *mousePosOld) / pixelScale;
            // Get elapsed time since last frame
            elapsed = clock.getElapsedTime().asSeconds();
            clock.restart();

			// diff
			layerHandler->update(worldData->getCharacter(0)->getPosition().x - characterXPos);
			characterXPos = worldData->getCharacter(0)->getPosition().x;

			// Every 10th frame:
			if(counter == 10) {
				int renderFps = (int)(1 / elapsed);

				worldDataMutex.lock();
				int logicFps = worldData->getLogicFps();
				worldDataMutex.unlock();

				std::string renderFpsString = convertInt(renderFps);
				renderFpsTxt->setString("Render fps: " + renderFpsString);
				std::string logicFpsString = convertInt(logicFps);
				logicFpsTxt->setString("Logic fps:  " + logicFpsString);

				counter = 0;
			} else {
				counter++;
			}
	}

	void WorldView::update()
	{

		tempLoop();
		calculateCam();


		// Access world data
		//worldDataMutex.lock();

		for(unsigned int i=0;i<characters.size();i++) {
			((CharacterView*)characters.at(i))->updateAnimation(elapsed);
		}

		updatePositions();
		updateHUD();
		//layerHandler->update(1);


		// Unlock world data mutex
		//worldDataMutex.unlock();

	}

	void WorldView::draw(sf::RenderTarget& window, sf::RenderStates states) const {

			// Set world view so we can render the world in world coordinates
			window.setView(*camera);

            // Render World.
			drawWorld( window );

			window.draw(*layerHandler);

			// Render UI.
			drawHUD( window );

			// Save mouse position for next frame
			*mousePosOld = *mousePos;
	}

	//////////////////////////////
	// Initialize everything.
	// Change SFML settings, etc.
	//////////////////////////////
	void WorldView::initialize() {
		// Set up and initialize render window
		// Don't display mouse cursor
		//window->setMouseCursorVisible(false);

		// The path to resources
		resourcesDir = "resources/";

		// Background stuff
		float screenWidth = float(window->getSize().x);
		float screenHeight = float(window->getSize().y);

		backgroundTexture = new sf::Texture();
		backgroundTexture->loadFromFile("resources/bg.png");
		backgroundSprite = new sf::Sprite();
		backgroundSprite->setTexture(*backgroundTexture);
		backgroundSprite->setOrigin(screenWidth / 2 * pixelScale, screenHeight / 2 * pixelScale);
		backgroundSprite->setPosition(-20, -10);
		backgroundSprite->scale(0.02f, 0.02f);

		sunTexture = new sf::Texture();
		sunTexture->loadFromFile("resources/sun.jpg");
		sunSprite = new sf::Sprite();
		sunSprite->setTexture(*sunTexture);
		sunSprite->setPosition(-20, -10);
		sunSprite->scale(0.01, 0.01);
		layerHandler->addLayer(*sunSprite, -0.05f);

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

		//----SFML stuff----
		sf::Vector2f center(0,0);
		sf::Vector2f halfSize(screenWidth / 2 * pixelScale, screenHeight / 2 *pixelScale);

		// Intialize our camera.
		this->zoomLevel = 0;	// We start at 0,
		this->zoomLevelMax = 10;// 10 is our maximum zoomed-in level.
		camera = new sf::View(center * pixelScale, halfSize * pixelScale);
		camera->zoom( 1.5 );

		// Rotate the view 180 degrees
		camera->setRotation(180);

		//------------------
		// Instantiate stuff.
		mousePos = new sf::Vector2f(0,0);
		mousePosWindow = new sf::Vector2i(0,0);
		mousePosOld = new sf::Vector2f(0,0);
		mouseSpeed = new sf::Vector2f(0,0);

		// Initialize the HUD.
		this->initHUD();

		// Red dot?
		dotTex = new sf::Texture();
		dotSpr = new sf::Sprite();
		if(!dotTex->loadFromFile("resources/reddot.png"))
			std::cout << "Failed to load texture: reddot.png" << std::endl;
		dotSpr->setTexture(*dotTex);
		dotSpr->setOrigin(32, 32);
		dotSpr->setScale(0.5f, 0.5f);

		//instantiate map graphics
		constructMapGraphics();

		createCharacterViews();

		std::cout << "Render window initialized!" << std::endl;
	}


	/////////////////////////////////
	/// Initializes all HUD elements.
	/////////////////////////////////
	void WorldView::initHUD() {
		const int WIDTH = window->getSize().x;
		const int HEIGHT = window->getSize().y;
		int x,y;

		//------- Create "Kills" sprite. -------
		killsTexture = new sf::Texture();
		if (!killsTexture->loadFromFile((resourcesDir+"kills.png"))) {
			std::cout << "Failed to load texture: kills.png" << std::endl;
		}
		killsSprite = new sf::Sprite();
		killsSprite->setTexture(*killsTexture);
		x = ((WIDTH)/2) - killsSprite->getTexture()->getSize().x;
		y = 0;
		killsSprite->setPosition(float(x),float(y));
		// TODO: uncomment below line and fix the positioning error that occurs.
		//killsSprite.setScale(WIDTH / 1920, HEIGHT / 1080);

		// Create text label to display kill count.
		killsText = new sf::Text("0");
		killsText->setFont(*fontGothic);
		killsText->setCharacterSize(60);
		killsText->setStyle(sf::Text::Regular);
		// TODO: Fix positioning. Fails for strings of length>1.
		x = int(killsSprite->getPosition().x + (float(WIDTH)/12.5f));
		y = int(killsSprite->getPosition().y + (float(HEIGHT)/18.0f));
		killsText->setPosition(float(x), float(y));


		//------- Create "Deaths" sprite. -------
		deathsTexture = new sf::Texture();
		// Load image file
		if (!deathsTexture->loadFromFile((resourcesDir+"deaths.png"))) {
			std::cout << "Failed to load texture: deaths.png" << std::endl;
		}
		deathsSprite = new sf::Sprite();
		deathsSprite->setTexture(*deathsTexture);
		x = ((WIDTH)/2);
		y = 0;
		deathsSprite->setPosition(float(x),float(y));
		// TODO: read above.
		//deathsSprite.setScale(WIDTH / 1920, HEIGHT / 1080);

		deathsText = new sf::Text("0");
		deathsText ->setFont(*fontGothic);
		deathsText ->setCharacterSize(60);
		x = int(deathsSprite->getPosition().x + (WIDTH/9));  // TODO: kinda hardcoded.
		y = int(deathsSprite->getPosition().y + (HEIGHT/18));// doesn't work for all res's?
		deathsText->setPosition(float(x), float(y));

		//-------- Ammo sprite. ---------
		// ammo sprite.
		ammoSprite = new HUDSprite(resourcesDir + "ammo.png", 12);
		x = 0;
		y = (HEIGHT) - ammoSprite->getHeight();
		ammoSprite->setPosition(float(x),float(y));
		//ammoSprite->setScale(WIDTH / 1920, HEIGHT / 1080);

		//--------- HP sprite. ---------.
		hpSprite = new HUDSprite(resourcesDir + "hp.png", 9);
		x = (WIDTH)  - hpSprite->getWidth();
		y = (HEIGHT) - hpSprite->getHeight();
		hpSprite->setPosition(float(x),float(y));
		//hpSprite->setScale(WIDTH / 1920, HEIGHT / 1080);
		//------------------------------

	}

	// Fetches all character models,
	// and creates their corresponding views.
	void WorldView::createCharacterViews() {
		worldDataMutex.lock();

		// Fetch character models.
		std::vector<Character*>* characterModels = worldData->getCharacters();
		std::cout<<"Characters: "<<worldData->getCharacters()->size()<<std::endl;
		// Loop through them,
		for (unsigned int i=0;i<characterModels->size();i++) {
			// create for each one a visual representation,
			CharacterView* view = new CharacterView(characterModels->at(i));
			// and add it to our list of CharacterViews.
			this->characters.push_back( view );
		}
		worldDataMutex.unlock();
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
	}

	void WorldView::updatePositions()
	{
		// Set sight position
		dotSpr->setPosition(float(mousePosWindow->x), float(mousePosWindow->y));

		updateBulletsPos();
		updateCharactersPos();
	}

	void WorldView::updateBulletsPos()
	{
		//worldViewMutex.lock();
		updateVectorPos(bullets);
		//worldViewMutex.unlock();
	}

	void WorldView::updateCharactersPos()
	{
		//worldViewMutex.lock();
		updateVectorPos(characters);
		//worldViewMutex.unlock();
	}

	void WorldView::updateHUD()
	{

		worldDataMutex.lock();

		Character currentCharacter = *worldData->getCurrentCharacter();
		std::ostringstream kills, deaths; // (convert short->string)

		kills << currentCharacter.getKills();
		killsText->setString(kills.str());
		deaths << currentCharacter.getDeaths();
		deathsText->setString(deaths.str());

		ammoSprite->setState(currentCharacter.getClip());
		hpSprite->setState(currentCharacter.getHealthState());

		worldDataMutex.unlock();
	}

	// better name
	void WorldView::drawVector(const std::vector<GameObjectView*>& vector, sf::RenderTarget& window) const
	{
		std::vector<GameObjectView*>::const_iterator it;
		for ( it = vector.begin() ; it < vector.end(); it++ )
			window.draw(**it);
	}

	void WorldView::drawWorld(sf::RenderTarget& window) const
	{
		drawEnvironment(window);
		drawCharacters(window);
		drawBullets(window);
		// Draw light.
		//window.draw(*lightSpr, sf::BlendAdd);
	}

	void WorldView::drawEnvironment(sf::RenderTarget& window) const
	{
		window.draw(*backgroundSprite);
		window.draw(*ground);
		window.draw(*ground2);
		window.draw(*ground3);
		window.draw(*ground4);
	}

	void WorldView::drawBullets(sf::RenderTarget& window) const
	{
		//worldViewMutex.lock();
		drawVector(bullets, window);
		//worldViewMutex.unlock();
	}

	void WorldView::drawCharacters(sf::RenderTarget& window) const
	{
		//worldViewMutex.lock();
		drawVector(characters, window);
		//worldViewMutex.unlock();
	}

	void WorldView::drawHUD(sf::RenderTarget& window) const {
		// Set default view so we can render the ui in window coordinates
		window.setView(this->window->getDefaultView());
		window.draw(*dotSpr);
		// Draw hud
		if(ConfigHandler::instance().getBool("r_drawhud")) {
			window.draw(*killsSprite);
			window.draw(*killsText);

			window.draw(*deathsSprite);
			window.draw(*deathsText);

			window.draw(*ammoSprite);
			window.draw(*hpSprite);
		}
		// Draw debug labels
		if(ConfigHandler::instance().getBool("s_debugmode"))
		{
			window.draw(*renderFpsTxt);
			window.draw(*logicFpsTxt);
		}
	}


	// better name maybe
	void WorldView::updateVectorPos(std::vector<GameObjectView*>& vector)
	{
		std::vector<GameObjectView*>::iterator it;
		for ( it = vector.begin() ; it < vector.end(); it++ ) {
			(*it)->updatePosition();
		}
	}

	void WorldView::calculateCam()
	{
		worldDataMutex.lock();
		// Calculate camera position (somehwere between character and mouse)
		b2Vec2 position = worldData->getCurrentCharacter()->getBody()->GetPosition();
		float32 angle = worldData->getCurrentCharacter()->getBody()->GetAngle();
		//testSpr.setPosition(position.x*pixelScale,position.y*pixelScale);
		worldDataMutex.unlock();

		float x = (((position.x + mousePos->x) / 2 + position.x) / 2 + position.x) / 2;
		float y = (((position.y + mousePos->y) / 2 + position.y) / 2 + position.y) / 2;

		camera->setCenter(x * pixelScale, y * pixelScale);
	}

	////////////////////////////////////////////////////////////
	// Destructor
	////////////////////////////////////////////////////////////
    WorldView::~WorldView()
    {
		// Destroy all characters.
		for(unsigned int i=0;i<characters.size();i++) {
			delete characters.at(i);
		}// Destroy all bullets.
		for(unsigned int i=0;i<bullets.size();i++) {
			delete bullets.at(i);
		}

		// Destroy HUD.
		delete killsTexture;
		delete deathsTexture;
		delete killsSprite;
		delete deathsSprite;
		delete hpSprite;
		delete ammoSprite;

		// Destroy debug labels.
		delete fontGothic;
		delete renderFpsTxt;
		delete logicFpsTxt;

		// Background.
		delete backgroundTexture;
		delete backgroundSprite;

		// TODO: This (as well as their creation) should be dynamic.
		delete ground;
		delete ground2;
		delete ground3;
		delete ground4;

		delete dotTex;
		delete dotSpr;

		delete mousePosOld;
		delete mousePos;
		delete mousePosWindow;
		delete mouseSpeed;
    }

}



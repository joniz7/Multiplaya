////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
// Class header
#include "worldview.h"
#include "../../model/worlddata.h"

#include "../../includes/Global.h"

#include "../../services/confighandler.h"

#include "../animatedsprite.h"

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

		counter = 0;
		elapsed = 0;

		initialize();
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
		backgroundTexture->loadFromFile("resources/ui/bg.png");
		backgroundSprite = new sf::Sprite();
		backgroundSprite->setTexture(*backgroundTexture);
		backgroundSprite->setOrigin(screenWidth / 2 * PIXEL_SCALE, screenHeight / 2 * PIXEL_SCALE);
		backgroundSprite->setPosition(-20, -10);
		backgroundSprite->scale(0.02f, 0.02f);

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
		sf::Vector2f halfSize(screenWidth / 2 * PIXEL_SCALE, screenHeight / 2 *PIXEL_SCALE);

		// Intialize our camera.
		this->zoomLevel = 0;	// We start at 0,
		this->zoomLevelMax = 10;// 10 is our maximum zoomed-in level.
		camera = new sf::View(center * PIXEL_SCALE, halfSize * PIXEL_SCALE);
		camera->zoom( 1.5 );

		// Rotate the view 180 degrees
		camera->setRotation(180);

		// Initialize the HUD.
		this->initHUD();

		// Red dot?
		dotTex = new sf::Texture();
		dotSpr = new sf::Sprite();
		if(!dotTex->loadFromFile("resources/ui/reddot.png"))
			std::cout << "Failed to load texture: reddot.png" << std::endl;
		dotSpr->setTexture(*dotTex);
		dotSpr->setOrigin(32, 32);
		dotSpr->setScale(0.5f, 0.5f);

		createCharacterViews();

		updateWorldVertices();

		std::cout << "Render window initialized!" << std::endl;
	}

		/////////////////////////////////
	/// Initializes all HUD elements.
	/////////////////////////////////
	void WorldView::initHUD() {
		const int WIDTH = window->getSize().x;
		const int HEIGHT = window->getSize().y;
		int x, y;

		//------- Create "Kills" sprite. -------
		killsTexture = new sf::Texture();
		if (!killsTexture->loadFromFile((resourcesDir + "ui/hud/kills.png"))) {
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
		if (!deathsTexture->loadFromFile((resourcesDir + "ui/hud/deaths.png"))) {
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
		ammoSprite = new HUDSprite(resourcesDir + "ui/hud/ammo.png", sf::Vector2i(3,4));
		x = 0;
		y = (HEIGHT) - ammoSprite->getHeight();
		ammoSprite->setPosition(float(x),float(y));
		//ammoSprite->setScale(WIDTH / 1920, HEIGHT / 1080);

		//--------- HP sprite. ---------.
		hpSprite = new HUDSprite(resourcesDir + "ui/hud/hp.png", sf::Vector2i(5,2));
		x = (WIDTH)  - hpSprite->getWidth();
		y = (HEIGHT) - hpSprite->getHeight();
		hpSprite->setPosition(float(x),float(y));
		//hpSprite->setScale(WIDTH / 1920, HEIGHT / 1080);
		//------------------------------
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
			worldViewMutex.lock();
			IBullet* bullet = ( IBullet* )object;
			addBullet(bullet);
			worldViewMutex.unlock();
		}
		else if (e == BULLET_DELETED)
		{
			worldViewMutex.lock();
			int i = ( intptr_t )object;
			deleteBullet(i);
			worldViewMutex.unlock();
		}
		else if (e == CHARACTER_ADDED)
		{
			std::cout << "Adding character to view" << std::endl;
			ICharacter* character = (ICharacter*)object;
			addCharacter(character);
		}
		else if (e == CHARACTER_DELETED)
		{
			int i = ( intptr_t )object;
			deleteCharacter(i);
		}
	}

	void WorldView::addBullet(IBullet* bullet)
	{
		bullets.push_back(  new BulletView( bullet ) );
	}

	// delete bullet at index i
	void WorldView::deleteBullet(int i)
	{
		BulletView* bullet = (BulletView*) bullets.at(i);
		bullets.erase(bullets.begin() + i );
		delete bullet;
	}

	void WorldView::addCharacter(ICharacter* character) {
		characters.push_back( new CharacterView( character ) );
	}

	void WorldView::deleteCharacter(int i)
	{
		//worldViewMutex.lock();
		CharacterView* character = (CharacterView*) characters.at(i);
		characters.erase(characters.begin() + i);
		delete character;
		//worldViewMutex.unlock();
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
		if (zoomLevel < zoomLevelMax) {
			camera->zoom(1.0f/1.1f);
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

	void WorldView::setMousePos(const sf::Vector2i& mousePosWindow)
	{
		this->mousePosWindow = mousePosWindow;
	}

	void WorldView::draw(sf::RenderTarget& window, sf::RenderStates states) const {
		// Set world view so we can render the world in world coordinates
		window.setView(*camera);
		// Render World.
		drawEnvironment(window);
		drawWorldGeo(window);
		drawCharacters(window);
		drawBullets(window);
		// Render UI.
		drawHUD( window );			
	}

	// Fetches all character models,
	// and creates their corresponding views.
	void WorldView::createCharacterViews() {
		worldDataMutex.lock();

		// Fetch character models.
		std::vector<ICharacter*>* characterModels = worldData->getCharacters();
		std::cout<<"Characters: "<<worldData->getCharacters()->size()<<std::endl;
		// Loop through them,
		for (unsigned int i = 0; i < characterModels->size(); i++) {
			// create for each one a visual representation,
			CharacterView* view = new CharacterView(characterModels->at(i));
			// and add it to our list of CharacterViews.
			this->characters.push_back( view );
		}
		worldDataMutex.unlock();
	}

	// better name
	void WorldView::drawVector(const std::vector<GameObjectView*>& vector, sf::RenderTarget& window) const
	{
		std::vector<GameObjectView*>::const_iterator it;
		for ( it = vector.begin() ; it < vector.end(); it++ )
			window.draw(**it);
	}

	void WorldView::drawWorldGeo(sf::RenderTarget& window) const
	{
		for(std::vector<sf::VertexArray*>::const_iterator it = worldGeo.begin(); it != worldGeo.end(); ++it)
			window.draw( (**it) );
	}

	void WorldView::drawEnvironment(sf::RenderTarget& window) const
	{
		window.draw(*backgroundSprite);
	}

	void WorldView::drawBullets(sf::RenderTarget& window) const
	{
		worldViewMutex.lock();
		drawVector(bullets, window);
		worldViewMutex.unlock();
	}

	void WorldView::drawCharacters(sf::RenderTarget& window) const
	{
		drawVector(characters, window);
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

	void WorldView::update()
	{
		updateFpsCounters();
		updateCamera();
		updateSightPos();

		// Access world data
		worldDataMutex.lock();
		updateVector(bullets);
		updateVector(characters);
		updateHUD();

		// Unlock world data mutex
		worldDataMutex.unlock();
	}

	void WorldView::updateSightPos()
	{
		dotSpr->setPosition( (float) mousePosWindow.x, (float) mousePosWindow.y);
	}

	void WorldView::updateFpsCounters()
	{
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
		} else
			counter++;
	}

	////////////////////////////////
	/// Refreshes the vertices representings
	/// the world physics geo.
	////////////////////////////////
	void WorldView::updateWorldVertices()
	{
		worldGeo.clear();

		worldDataMutex.lock();

		std::vector<WorldChain*> wee = *worldData->getChains();

		for(std::vector<WorldChain*>::iterator it = wee.begin(); it != wee.end(); ++it)
		{
			worldGeo.push_back( new sf::VertexArray() );
			
			std::vector<b2Vec2> vertices = *(*it)->getVertices();
			
			for(int i=0;i<vertices.size();i++)
			{
				worldGeo.back()->append( sf::Vertex( sf::Vector2f( (vertices.at(i).x)*PIXEL_SCALE , (vertices.at(i).y)*PIXEL_SCALE ) ) );
				worldGeo.back()->setPrimitiveType(sf::LinesStrip);
			}
		}
		worldDataMutex.unlock();
	}

	void WorldView::updateVector(std::vector<GameObjectView*>& vector)
	{
		worldViewMutex.lock();
		std::vector<GameObjectView*>::iterator it;
		for ( it = vector.begin() ; it < vector.end(); it++ ) {
			(*it)->update();
		}
		worldViewMutex.unlock();
	}

	void WorldView::updateCamera()
	{
		worldDataMutex.lock();
		// Calculate camera position (somehwere between character and mouse)
		const b2Vec2& position = worldData->getCurrentCharacter()->getBody()->GetPosition();
		const float32 angle = worldData->getCurrentCharacter()->getBody()->GetAngle();
		//testSpr.setPosition(position.x*PIXEL_SCALE,position.y*PIXEL_SCALE);
		worldDataMutex.unlock();

		sf::Vector2f mousePos = window->convertCoords(mousePosWindow, *getCamera());

		float x = (((position.x + mousePos.x) / 2 + position.x) / 2 + position.x) / 2;
		float y = (((position.y + mousePos.y) / 2 + position.y) / 2 + position.y) / 2;

		camera->setCenter(x * PIXEL_SCALE, y * PIXEL_SCALE);
	}

	void WorldView::updateHUD()
	{
		worldDataMutex.lock();

		ICharacter* currentCharacter = worldData->getCurrentCharacter();
		std::ostringstream kills, deaths; // (convert short->string)

		kills << currentCharacter -> getKills();
		killsText->setString(kills.str());
		deaths << currentCharacter->getDeaths();
		deathsText->setString(deaths.str());

		ammoSprite->setState(currentCharacter->getClip());
		hpSprite->setState(currentCharacter->getHealthState());

		worldDataMutex.unlock();
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
		delete killsText;
		delete deathsText;

		// Destroy debug labels.
		delete fontGothic;
		delete renderFpsTxt;
		delete logicFpsTxt;

		// Background.
		delete backgroundTexture;
		delete backgroundSprite;

		delete dotTex;
		delete dotSpr;
    }

}



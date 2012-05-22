////////////////////////////////////////////////////////////
/// World class. Takes care of game physics and logic
////////////////////////////////////////////////////////////
#ifndef WORLDVIEW_H_INCLUDED
#define WORLDVIEW_H_INCLUDED

// Other headers
#include <string>
#include <cstdlib>
#include <list>
#include <cmath>
#include <vector>

// SFML specific headers
#include "../sfml.h"

#include <iostream>
#include <sstream>

#include "CharacterView.h"
// Box2D specific headers
#include <Box2D.h>
#include "../defines.h"

// Game specific headers
#include "BulletView.h"
#include "HUDSprite.h"

#include "../util/Observer.h"
#include "GameObjectView.h"

// Not sure if worldViewMutex should be defined here..
#include "../global.h"

#include "Screen.h"
#include "GUIElements/GUIElement.h"
#include "LayerHandler.h"

namespace mp
{
	//Forward declaration so WorldView can have a WorldData pointer
	class WorldData;
	class CharacterView;
	class BulletView;
	class GameObjectView;
	class HUDSprite;
    
	class WorldView : public Screen, public Observer
    {
        public:
			WorldView( WorldData* worldData, sf::RenderWindow* window );
			void exec();

			/// returns sf::View pointing to camera
			sf::View* getView() { return camera; }
            ~WorldView();

			virtual void notify(Event e, void* object);
			CharacterView* getCharacter(int i) { return (CharacterView*) characters.at(i); }
			virtual void update();
			virtual GUIElement* getElement(std::string element) { return buttons[element]; }
			void zoom(float zoomFactor);
			void zoomIn();
			void zoomOut();
			sf::View* getCamera() { return camera; }

			void characterMoved(float moved);
			
		protected:
    		
		private:
			std::map<std::string, GUIElement*> buttons;

			// The directory of resource files.
			std::string resourcesDir;
			
			// HUD textures.
			sf::Texture* killsTexture;
			sf::Texture* deathsTexture;
			
			// HUD sprites.
			sf::Sprite* killsSprite;
			sf::Sprite* deathsSprite;
			HUDSprite* hpSprite;
			HUDSprite* ammoSprite;
			sf::Text* killsText;
			sf::Text* deathsText;
			
			mutable sf::RenderWindow* window;

			WorldData* worldData;
			sf::View* camera;
			unsigned int zoomLevel;
			unsigned int zoomLevelMax;
			
			std::vector<GameObjectView*> characters;
			std::vector<GameObjectView*> bullets;
			// Clock for frame time counting
			sf::Clock clock;
			sf::Font* fontGothic;

			sf::Text* renderFpsTxt;
			sf::Text* logicFpsTxt;

			sf::Texture* backgroundTexture;
			sf::Sprite* backgroundSprite;

			sf::RectangleShape* ground;
			sf::RectangleShape* ground2;
			sf::RectangleShape* ground3;
			sf::RectangleShape* ground4;

			sf::Texture* dotTex;
			sf::Sprite* dotSpr;
			
			sf::Vector2f* mousePosOld;
			sf::Vector2f* mousePos;
			sf::Vector2i* mousePosWindow;
			sf::Vector2f* mouseSpeed;

			void addBullet(Bullet* bullet);
			void deleteBullet(int i);

			void addCharacter(Character* character);
			void deleteCharacter(int i);

			void constructMapGraphics();

			void calculateCam();
			void updateHUD();

			void updatePositions();
			void updateBulletsPos();
			void updateCharactersPos();
			
			void createCharacterViews();

			void initialize();
			void initHUD();
			void initMusic();

			virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;
			void drawWorld(sf::RenderTarget& window) const;
			void drawEnvironment(sf::RenderTarget& window) const;
			void drawBullets(sf::RenderTarget& window) const;
			void drawCharacters(sf::RenderTarget& window) const;
			void drawHUD(sf::RenderTarget& window) const;
			void drawVector(const std::vector<GameObjectView*>& vector, sf::RenderTarget& window) const;

			void updateVectorPos(std::vector<GameObjectView*>& vector);

			virtual void hover (const sf::Vector2i& mousePos) { }

			void tempLoop();

			int counter;
			float elapsed;

			LayerHandler* layerHandler;
			sf::Texture* sunTexture;
			sf::Sprite* sunSprite;

			float characterXPos;
    };
}

#endif
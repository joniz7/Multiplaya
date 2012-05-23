////////////////////////////////////////////////////////////
/// World class. Takes care of game physics and logic
////////////////////////////////////////////////////////////
#ifndef WORLDVIEW_H_INCLUDED
#define WORLDVIEW_H_INCLUDED

// Other headers
#include <string>
#include <cstdlib>
#include <cmath>
#include <vector>

// SFML specific headers
#include <SFML/Graphics.hpp>

#include <iostream>
#include <sstream>

// Box2D specific headers
#include <Box2D.h>

// Game specific headers
#include "../CharacterView.h"
#include "../BulletView.h"
#include "../HUDSprite.h"

// Not sure if worldViewMutex should be defined here..
#include "../../includes/Global.h"

#include "Screen.h"
#include "../GUIElements/GUIElement.h"
#include "../../services/input.h"

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

			void setMousePos(const sf::Vector2i& mousePos);

			void characterMoved(float moved);

			void resetClock(){
				clock.restart();
			}

			void setClock(){
				elapsed = clock.getElapsedTime().asSeconds();
			}

			void updateWorldVertices();

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

			sf::Texture* dotTex;
			sf::Sprite* dotSpr;

			sf::Vector2i mousePosWindow;

			std::vector<sf::VertexArray*> worldGeo;

			void addBullet(IBullet* bullet);
			void deleteBullet(int i);

			void addCharacter(ICharacter* character);
			void deleteCharacter(int i);



			void createCharacterViews();

			void initialize();
			void initHUD();
			void initMusic();



			virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;
			void drawWorldGeo(sf::RenderTarget& window) const;
			void drawEnvironment(sf::RenderTarget& window) const;
			void drawBullets(sf::RenderTarget& window) const;
			void drawCharacters(sf::RenderTarget& window) const;
			void drawHUD(sf::RenderTarget& window) const;
			void drawVector(const std::vector<GameObjectView*>& vector, sf::RenderTarget& window) const;

			void updateVector(std::vector<GameObjectView*>& vector);

			virtual void hover (const sf::Vector2i& mousePos) { }

			void updateFpsCounters();

			void updateCamera();
			void updateHUD();
			void updateSightPos();


			int counter;
			float elapsed;
    };
}

#endif

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

// Game specific headers
#include "../game.h"
#include "BulletView.h"

#include "../util/Observer.h"
#include "GameObjectView.h"

// Not sure if worldViewMutex should be defined here..
#include "../global.h"

namespace mp
{
	//Forward declaration so WorldView can have a WorldData pointer
	class WorldData;
	class CharacterView;
	class BulletView;
	class GameObjectView;
    
	class WorldView : public Observer
    {
        public:
			WorldView( WorldData* worldData );
			void exec();
			sf::View* getView() { return worldView; }
            ~WorldView();
			virtual void notify(std::string e, void* object);
			CharacterView* getCharacter(int i) { return (CharacterView*) characters.at(i); }
			
		protected:
    		
		private:
			float pixelScale;
			//CharacterView* charView;
			sf::Texture hudTex;
			sf::Sprite hudSpr;
			WorldData* worldData;
			sf::View* worldView;
			sf::RenderWindow* window;
			
			std::vector<GameObjectView*> characters;
			std::vector<GameObjectView*> bullets;
			// Clock for frame time counting
			sf::Clock clock;
			sf::Font* fontGothic;

			sf::Text* renderFpsTxt;
			sf::Text* logicFpsTxt;

			sf::RectangleShape* background;
			sf::RectangleShape* ground;
			sf::RectangleShape* ground2;
			sf::RectangleShape* ground3;
			sf::RectangleShape* ground4;

			sf::Sprite* lightSpr;
			sf::Sprite* dotSpr;
			
			sf::Vector2f* mousePos;
			sf::Vector2i* mousePosWindow;
			sf::Vector2f* mousePosOld;
			sf::Vector2f* mouseSpeed;

			void addBullet(Bullet* bullet);
			void deleteBullet(int i);

			void handleEvents();

			void constructMapGraphics();

			void calculateCam();
			
			void updateObjects(int elapsed);
			void updateBullets();
			void updateCharacters(int elapsed);
			//void updateVectorPosition();

			void initialize();
			void createCharacterViews();
			void drawWorld();
			void drawEnvironment();
			void drawBullets();
			void drawCharacters();
			void drawUI();
			void drawVector(std::vector<GameObjectView*>& vector);
			void updateVectorPos(std::vector<GameObjectView*>& vector);

    };
}

#endif
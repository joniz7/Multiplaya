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
	class AnimatedSprite; // TODO remove, after sprites has been fully moved to CharacterView.
    
	class WorldView : public Observer
    {
        public:
			WorldView( WorldData* worldData );
			void exec();
			sf::View* getView() { return worldView; }
            ~WorldView();
			virtual void notify(Event e, void* object);
			CharacterView* getCharacter(int i) { return (CharacterView*) characters.at(i); }
			
		protected:
    		
		private:
			float pixelScale;
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

			sf::Texture* lightTex;
			sf::Sprite* lightSpr;
			sf::Texture* dotTex;
			sf::Sprite* dotSpr;
			// TODO remove, after sprites has been fully moved to CharacterView.
			mp::AnimatedSprite* characterSprite;
			sf::Texture* characterTexture;

			sf::Vector2f* mousePosOld;
			sf::Vector2f* mousePos;
			sf::Vector2i* mousePosWindow;
			sf::Vector2f* mouseSpeed;

			void addBullet(Bullet* bullet);
			void deleteBullet(int i);

			void handleEvents();

			void constructMapGraphics();

			void calculateCam();
			
			void updatePositions();
			void updateBulletsPos();
			void updateCharactersPos();
			
			void createCharacterViews();

			void initialize();
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
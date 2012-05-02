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

namespace mp
{
	//Forward declaration so WorldView can have a WorldData pointer
	class WorldData;
	class CharacterView;
	class BulletView;
    
	class WorldView : public Observer
    {
        public:
			WorldView( WorldData* worldData );
			void exec();
			sf::View* getView() { return worldView; }
            ~WorldView();
			virtual void notify(std::string e, void* object);
			CharacterView* getCharacter(int i){ return &characters.at(i); };
			
		protected:
    		
		private:
			float pixelScale;
			//CharacterView* charView;
			sf::Texture hudTex;
			sf::Sprite hudSpr;
			WorldData* worldData;
			sf::View* worldView;
			sf::RenderWindow* window;
			sf::Vector2f* mousePos;
			std::vector<CharacterView> characters;
			std::vector<BulletView> bullets;

			sf::RectangleShape* background;
			sf::RectangleShape* ground;
			sf::RectangleShape* ground2;
			sf::RectangleShape* ground3;
			sf::RectangleShape* ground4;
			sf::RectangleShape* blueBox;
			sf::Sprite* lightSpr;
			sf::Sprite* dotSpr;
			
			sf::Vector2i* mousePosWindow;
			sf::Vector2f* mouseSpeed;

			void handleEvents();

			void constructMapGraphics();

			void calculateCam();
			
			void updatePositions();
			void updateBulletsPos();
			void updateCharactersPos();
			//void updateVectorPosition();

			void drawGraphics();
			void drawEnvironment();
			void drawBullets();
			void drawCharacters();
			//void drawVector(std::vector<sf::Drawable*>& vector);

    };
}

#endif
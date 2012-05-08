//////////////////////////////////////////////////////////////
/// CharacterView class. Graphical representation of Character
//////////////////////////////////////////////////////////////
#ifndef CHARACTER_VIEW_H
#define CHARACTER_VIEW_H

// SFML specific headers
#include "../sfml.h"

// Box2D specific headers
#include <Box2D.h>

// Game specific headers
#include "../game.h"
#include "animatedsprite.h"
#include "../util/Observer.h"
#include "GameObjectView.h"

namespace mp
{
	class Character;

	class CharacterView : public GameObjectView
	{
		public:
			CharacterView(Character* character);
			~CharacterView();
			void updatePosition();
			void updateSprite(int elapsed);

		private:
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
			void createAnimatedSprite();
			Character* character;
			//sf::Sprite* sprite;

			sf::Texture* frameTexture;
			AnimatedSprite* sprite;

			bool facedRightLastUpdate;
	};
}

#endif
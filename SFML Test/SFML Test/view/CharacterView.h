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

namespace mp
{
	class Character;

	class CharacterView : public sf::Drawable
	{
		public:
			//CharacterView(Character* model, sf::Sprite* sprite);
			CharacterView(Character* character, AnimatedSprite* sprite);
			~CharacterView();
			void updatePosition();
		private:
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
			Character* character;
			//sf::Sprite* sprite;
			AnimatedSprite* sprite;

			bool facedRightLastUpdate;

	};
}

#endif
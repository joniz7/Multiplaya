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

	class CharacterView : public sf::Drawable, public Observer
	{
		public:
			//CharacterView(Character* model, sf::Sprite* sprite);
			CharacterView(Character* model, AnimatedSprite* sprite);
			~CharacterView();
			virtual void notify(std::string e, void* object);
			void updatePosition();
		private:
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
			Character* model;
			//sf::Sprite* sprite;
			AnimatedSprite* sprite;

	};
}

#endif
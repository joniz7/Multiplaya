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
			//CharacterView(Character* model, sf::Sprite* sprite);
			CharacterView(Character* character, AnimatedSprite* sprite);
			CharacterView(Character* character);
			~CharacterView();
			void updateAnimation(int elapsed);
			void updatePosition();
		private:
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
			Character* character;
			//sf::Sprite* sprite;
			AnimatedSprite* sprite;
			sf::Texture* texture;

			bool facedRightLastUpdate;

	};
}

#endif
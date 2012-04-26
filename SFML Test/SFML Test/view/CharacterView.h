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

namespace mp
{
	class CharacterView : public sf::Drawable
	{
		public:
			//CharacterView(Character* model);
			CharacterView();
			~CharacterView();
		private:
			Character* model;
			sf::RectangleShape* bulletVis;
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	};
}

#endif
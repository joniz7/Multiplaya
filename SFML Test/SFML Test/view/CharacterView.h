//////////////////////////////////////////////////////////////
/// CharacterView class. Graphical representation of Character
//////////////////////////////////////////////////////////////
#ifndef CHARACTER_VIEW_H
#define CHARACTER_VIEW_H

// Game specific headers
#include "../game.h"

namespace mp
{
	class Character;

	class CharacterView
	{
		public:
			CharacterView(Character* model);
			~CharacterView();
		private:
			Character* model;
	};
}
#endif
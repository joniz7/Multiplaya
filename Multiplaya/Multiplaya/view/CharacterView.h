//////////////////////////////////////////////////////////////
/// CharacterView class. Graphical representation of Character
//////////////////////////////////////////////////////////////
#ifndef CHARACTER_VIEW_H
#define CHARACTER_VIEW_H

#include "GameObjectView.h"
// Game specific headers
#include "../global.h"
#include "../model/character.h"
#include "animatedsprite.h"

#include "../services/resourcehandler.h"

namespace mp
{
	class Character;
	class CharacterSprite;

	class CharacterView : public GameObjectView
	{
		public:
			//CharacterView(Character* model, sf::Sprite* sprite);
			CharacterView(ICharacter* character, CharacterSprite* sprite);
			CharacterView(ICharacter* character);
			~CharacterView();
			void updateAnimation(float elapsed);
			void updatePosition();

			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		private:
			bool facingLeft;
			
			ICharacter* character;
			AnimatedSprite* sprite;

	};
}

#endif
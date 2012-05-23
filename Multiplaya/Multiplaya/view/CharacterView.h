//////////////////////////////////////////////////////////////
/// CharacterView class. Graphical representation of Character
//////////////////////////////////////////////////////////////
#ifndef CHARACTER_VIEW_H
#define CHARACTER_VIEW_H

#include "GameObjectView.h"
// Game specific headers
#include "../includes/Global.h"
#include "../model/ICharacter.h"
#include "animatedsprite.h"

#include "../services/resourcehandler.h"

namespace mp
{
	class Character;
	class CharacterSprite;

	/**
	 * The visual representation of a character.
	 *
	 * Is tied to an ICharacter, which we poll continuously
	 * for its position and its state (walking, jumping etc).
	 */
	class CharacterView : public GameObjectView
	{
		public:
			CharacterView(ICharacter* character);
			~CharacterView();

			void update();
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		private:
			bool facingLeft;
			
			ICharacter* character;
			AnimatedSprite* sprite;

			void updateAnimation(float elapsed);

	};
}

#endif
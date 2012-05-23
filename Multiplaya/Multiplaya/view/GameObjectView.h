////////////////////////////////////////////////////////////
/// GameObjectView interface. 
////////////////////////////////////////////////////////////
#ifndef GAME_OBJECT_VIEW_H
#define GAME_OBJECT_VIEW_H

#include <SFML/Graphics.hpp>
#include "../includes/Defines.h"

namespace mp
{
	/**
	 * The visual representation of a GameObject.
	 */ 
	class GameObjectView : public sf::Drawable
	{
		public:
			virtual void updatePosition() = 0;
	};
}
#endif // OBSERVER_H
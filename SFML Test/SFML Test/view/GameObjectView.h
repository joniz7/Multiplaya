////////////////////////////////////////////////////////////
/// GameObjectView interface. 
////////////////////////////////////////////////////////////
#ifndef GAME_OBJECT_VIEW_H
#define GAME_OBJECT_VIEW_H

#include "../sfml.h"
#include "../defines.h"

namespace mp
{
	class GameObjectView : public sf::Drawable
	{
		public:
			virtual void updatePosition() = 0;
	};
}
#endif // OBSERVER_H
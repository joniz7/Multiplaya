#ifndef CONTACTLISTENER_H_INCLUDED
#define CONTACTLISTENER_H_INCLUDED

// Box2D specific headers
#include <Box2D.h>
#include <iostream>
#include "GameObject.h"

namespace mp {

	/**
	 * A class which inherits Box2D's contactlistener.
	 * Reacts when two objects collide with eachother,
	 * and calls both of theirs onCollision() methods.
	 */
	class ContactListener : public b2ContactListener
	{
		public:
			ContactListener();
			~ContactListener();
			void BeginContact(b2Contact* contact);
			void EndContact(b2Contact* contact);
		private:

	};
}

#endif
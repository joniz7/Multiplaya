#ifndef CONTACT_LISTENER_INCLUDED
#define CONTACT_LISTENER_INCLUDED

// Box2D specific headers
#include <Box2D.h>

#include "worlddata.h"
#include <iostream>
#include "GameObject.h"

namespace mp {
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
#include "ContactListener.h"

namespace mp {

	ContactListener::ContactListener(WorldData* worldData)
	{
		this->worldData = worldData;
	}


	ContactListener::~ContactListener()
	{
	}


	void ContactListener::BeginContact(b2Contact* contact) {
		void* fixtureAUserData = contact->GetFixtureA()->GetUserData();
		void* fixtureBUserData = contact->GetFixtureB()->GetUserData();
		// read more in box2d manual, look for better way
		if (fixtureAUserData && fixtureBUserData) {
			GameObject* a = static_cast<GameObject*>( fixtureAUserData );
			GameObject* b = static_cast<GameObject*>( fixtureBUserData );
			b->onCollision(a);
			a->onCollision(b);
		}
			


		/*//check if fixture A was the foot sensor
		void* fixtureAUserData = contact->GetFixtureA()->GetUserData();
		void* fixtureBUserData = contact->GetFixtureB()->GetUserData();
         if ( (int)fixtureAUserData == 1 || (int)fixtureBUserData == 1 )
			 worldData->getCharacter(1)->setGrounded(true);
              */
    }
  
	void ContactListener::EndContact(b2Contact* contact) {
       /* //check if fixture A was the foot sensor
		void* fixtureAUserData = contact->GetFixtureA()->GetUserData();
		void* fixtureBUserData = contact->GetFixtureB()->GetUserData();

       if ( (int)fixtureAUserData == 1 || (int)fixtureBUserData == 1)
            worldData->getCharacter(1)->setGrounded(false);
			*/
	}
}
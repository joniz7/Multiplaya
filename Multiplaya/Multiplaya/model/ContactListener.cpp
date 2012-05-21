#include "ContactListener.h"

namespace mp {

	ContactListener::ContactListener()
	{
	}


	ContactListener::~ContactListener()
	{
	}


	void ContactListener::BeginContact(b2Contact* contact) {
		void* fixtureAUserData = contact->GetFixtureA()->GetUserData();
		void* fixtureBUserData = contact->GetFixtureB()->GetUserData();
		// read more in box2d manual, look for better way
		if (fixtureAUserData && fixtureBUserData) {
			GameObject* gameObjectA = static_cast<GameObject*>( fixtureAUserData );
			GameObject* gameObjectB = static_cast<GameObject*>( fixtureBUserData );
			gameObjectB->onCollision(gameObjectA);
			gameObjectA->onCollision(gameObjectB);
		}
	}

	void ContactListener::EndContact(b2Contact* contact) {
		void* fixtureAUserData = contact->GetFixtureA()->GetUserData();
		void* fixtureBUserData = contact->GetFixtureB()->GetUserData();
		// read more in box2d manual, look for better way
		if (fixtureAUserData && fixtureBUserData) {
			GameObject* gameObjectA = static_cast<GameObject*>( fixtureAUserData );
			GameObject* gameObjectB = static_cast<GameObject*>( fixtureBUserData );
			gameObjectB->onNoCollision(gameObjectA);
			gameObjectA->onNoCollision(gameObjectB);
		}
	}
}

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "worldchain.h"

namespace mp
{
	////////////////////////////////////////////////////////////
	// Constructor
	////////////////////////////////////////////////////////////
	WorldChain::WorldChain(b2World* world, b2Vec2 vertices[], int length, float friction)
	{
		// Save vertices
		for(int i=0;i<length;i++)
			verticeList.push_back(vertices[i]);

		b2ChainShape chain;
		chain.CreateChain(vertices, length);

		b2BodyDef bodyDef;
		bodyDef.type = b2_staticBody;
		b2Body* body = world->CreateBody(&bodyDef);
		b2FixtureDef fixtureDef;
		fixtureDef.friction = 0.5f;
		fixtureDef.shape = &chain;
		b2Fixture* fixture = body->CreateFixture(&fixtureDef);
		fixture->SetUserData(this);

		this->world = world;
		this->body = body;
		this->objectType = wall;
	}

	void WorldChain::onCollision(GameObject* crashedWith)
	{
	}
	
	////////////////////////////////////////////////////////////
	// Destructor
	////////////////////////////////////////////////////////////
	WorldChain::~WorldChain()
	{
		world->DestroyBody(body);
	}
}

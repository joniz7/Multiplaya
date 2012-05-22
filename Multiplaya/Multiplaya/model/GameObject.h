////////////////////////////////////////////////////////////
/// Player class.  Checks user input and such.
////////////////////////////////////////////////////////////
#ifndef GAME_OBJECT_H_INCLUDED
#define GAME_OBJECT_H_INCLUDED

// Box2D specific headers
#include <Box2D.h>

namespace mp 
{
	class GameObject
	{
		public:
			// probably don't even need specific characterFootSensor maybe to avoid double collision or something, will investigate!
			enum ObjectType { character, bullet, wall, characterFootSensor, characterRightSensor, characterLeftSensor } objectType;
			// Called when we collide with another object.
			virtual void onCollision( GameObject* crashedWith ) = 0;
			// Called when previously mentioned collision ends.
			virtual void onNoCollision( GameObject* crashedWith ) = 0;
			virtual ~GameObject() {};

			b2Body* getBody(){ return body; }
			b2Vec2 getPosition(){return body->GetPosition();}

		protected:
			// needed?
			GameObject() {}
			b2Body* body;
			b2World* world;
			
		private:
			
	};
}

#endif
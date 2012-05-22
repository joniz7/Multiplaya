////////////////////////////////////////////////////////////
/// Dynamic game object
////////////////////////////////////////////////////////////
#ifndef DYNAMIC_GAME_OBJECT_H_INCLUDED
#define DYNAMIC_GAME_OBJECT_H_INCLUDED

#include "GameObject.h"
#include "../util/Observable.h"

namespace mp 
{
	class DynamicGameObject : public GameObject, public Observable
	{
		public:
			b2Vec2 getLinVelocity(){ return getBody()->GetLinearVelocity();} 
		protected:
			DynamicGameObject();

			void scheduleDeletion(Event e);

		private:
			bool deletionScheduled;

	};

}


#endif
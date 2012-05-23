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
			const b2Vec2& getLinVelocity();
			void setLinVelocity(b2Vec2 velocity);

		protected:
			DynamicGameObject();

			void scheduleDeletion(Event e);

		private:
			bool deletionScheduled;

	};

}


#endif
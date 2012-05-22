#ifndef I_CHARACTER_H_INCLUDED
#define I_CHARACTER_H_INCLUDED

#include "GameObject.h"
// Box2D specific headers
#include <Box2D.h>
#include "../util/Observable.h"

namespace mp
{
	class Bullet;
	class ICharacter : public GameObject, public Observable
	{
		public:
			virtual void jump() = 0;

			virtual void crouch() = 0;

			virtual void primaryFire(b2Vec2 &targetPos) = 0;
			virtual void secondaryFire() = 0;

			virtual void inflictDamage(Bullet* b) = 0;
			virtual void kill() = 0;

			virtual void setInvincible(float duration) = 0;
			virtual void setMovement(int direction) = 0;


	};
}
#endif
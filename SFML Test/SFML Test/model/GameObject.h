////////////////////////////////////////////////////////////
/// Player class.  Checks user input and such.
////////////////////////////////////////////////////////////
#ifndef GAME_OBJECT_H_INCLUDED
#define GAME_OBJECT_H_INCLUDED

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
		protected:
			GameObject() {};
			
	};
}

#endif
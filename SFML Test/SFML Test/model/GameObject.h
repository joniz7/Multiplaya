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
			virtual void onCollision( GameObject* crashedWith ) = 0;
			virtual ~GameObject() {};
		protected:
			GameObject() {};
			
	};
}

#endif
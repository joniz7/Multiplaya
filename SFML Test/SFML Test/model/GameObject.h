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
			enum ObjectType { character, bullet, wall } objectType;
			virtual void onCollision( GameObject* crashedWith ) = 0;
			virtual ~GameObject() {};
		protected:
			GameObject() {};
			
	};
}

#endif
#ifndef I_CHARACTER_H_INCLUDED
#define I_CHARACTER_H_INCLUDED

#include "DynamicGameObject.h"
#include "gameobjects/StandardBullet.h"

namespace mp
{
	/**
	 * An interface for characters.
	 * Holds data about positioning, health etc,
	 * and is used for manipulating the character
	 * with methods such as jump() and moveLeft().
	 */
	class ICharacter : public DynamicGameObject
	{
		public:
			virtual void jump() = 0;

			virtual void crouch() = 0;

			virtual void primaryFire(b2Vec2 &targetPos) = 0;
			virtual void secondaryFire() = 0;

			virtual void inflictDamage(IBullet* b) = 0;
			virtual void kill() = 0;

			virtual void setInvincible(float duration) = 0;
			virtual void setMovement(int direction) = 0;

			virtual sf::Int8 getClientID() = 0;
			virtual void setClientID(sf::Int8 ID) = 0;

			float32 getAngle() { return getBody()->GetAngle(); }

			virtual void update() = 0;

			virtual void moveLeft() = 0;
			virtual void moveRight() = 0;
			virtual void moveUp() = 0;
			virtual void moveDown() = 0;

			virtual void setPosition(b2Vec2 position, float32 angle) = 0;

			virtual void reload() = 0;

			virtual void setTouchingWallLeft(bool choice) = 0;
			virtual bool isTouchingWallLeft() = 0;

			virtual void setTouchingWallRight(bool choice) = 0;
			virtual bool isTouchingWallRight() = 0;

			virtual short getKills() = 0;
			virtual short getDeaths() = 0;

			bool isDead() { return dead; }
			void setDead(bool d) { dead = d; }

			virtual void setWallSliding(bool choice) = 0;
			virtual bool isWallSliding() = 0;

			virtual void setFloorSliding(bool choice) = 0;
			virtual bool isFloorSliding() = 0;

			virtual void setGrounded(bool choice) = 0;
			virtual bool isGrounded() = 0;

			virtual void setWalking(bool choice) = 0;
			virtual bool isWalking() = 0;

			virtual void setIsFacingLeft(bool choice) = 0;
			virtual bool isFacingLeft() = 0;

			virtual void setFlipping(bool choice) = 0;
			virtual bool isFlipping() = 0;

			virtual bool isFocusing() = 0;
			virtual void setFocusing(bool choice) = 0;

			virtual bool isBackwards() = 0;
			virtual void setBackwards(bool choice) = 0;

			// Should probably return enum instead
			virtual short getHealthState() = 0;
			virtual short getHealth() = 0;

			virtual short getClip() = 0;

			virtual bool isShooting() = 0;
			virtual bool isReloading() = 0;

			virtual void setTargetPos(b2Vec2 targetPos) = 0;
			virtual b2Vec2 getTargetPos() = 0;

			
			virtual void setHealth(short health) = 0;
			virtual void setKills(short kills) = 0;
			virtual void setDeaths(short deaths) = 0;
			virtual void incKills() = 0;	
		protected:
			bool dead;

	};
}
#endif
#include "Player.h"

namespace mp {
	Player::Player()
	{
	}

	void Player::setCharacter(Character* character)
	{
		this->character = character;
	}

	Player::~Player()
	{
	}

	void Player::update(const sf::Vector2f &mousePos) 
	{
		checkUserInput(mousePos);
	}

	void Player::checkUserInput(const sf::Vector2f &mousePos)
	{
		bool nullifyLinearDamping = true;	// Determines if we should nullify linear damping at the end of this frame
		character->setWallSliding(false);
		// Movement keys are pressed
		if( pressingKeyForMovingLeft() || pressingKeyForMovingRight() )
		{
			// Left movement key is pressed
			if ( pressingKeyForMovingLeft() && !pressingKeyForMovingRight() )	// Character should face left
			{
				worldDataMutex.lock();
				character->setIsFacingLeft(true);
				// Apply slide speed
				if(character->isTouchingWallLeft())
				{
					nullifyLinearDamping = false;
					character->getBody()->SetLinearDamping(10);
					character->setWallSliding(true);
				}

				worldDataMutex.unlock();
			}
			// Right movement key is pressed
			else if ( pressingKeyForMovingRight() && !pressingKeyForMovingLeft() )	// Character should face right
			{
				worldDataMutex.lock();
				character->setIsFacingLeft(false);
				// Apply slide speed
				if(character->isTouchingWallRight())
				{
					nullifyLinearDamping = false;
					character->getBody()->SetLinearDamping(10);
					character->setWallSliding(true);
				}

				worldDataMutex.unlock();
			}

			// If we're not trying to move in both directions at once
			if( !(pressingKeyForMovingLeft() && pressingKeyForMovingRight()) )
			{
				if ( pressingKeyForMovingLeft() && !pressingKeyForMovingRight() )
					if(character->isGrounded())
						moveLeft(18,50);
					else
						moveLeft(18,5);
				else if ( pressingKeyForMovingRight() && !pressingKeyForMovingLeft() )
					if(character->isGrounded())
						moveRight(18,50);
					else
						moveRight(18,5);

				if (pressingKeyForMovingLeft() || pressingKeyForMovingRight() && character->isGrounded()) {
					worldDataMutex.lock();
					character->setWalking(true);
					worldDataMutex.unlock();
				} 
				else {
					worldDataMutex.lock();
					character->setWalking(false);
					worldDataMutex.unlock();
				}
			}
		}

		if( !(pressingKeyForMovingLeft() || pressingKeyForMovingRight()) && character->isGrounded() )
		{
			// Set linear damping so we stop
			character->getBody()->SetLinearDamping(10);
			nullifyLinearDamping = false;
		}

		if ( pressingKeyForMovingUp() ) 
		{
			//moveUp();
		}
		if ( pressingKeyForMovingDown() ) 
		{
			moveDown();
		}
		if( pressingKeyForPrimaryFire() )
        {
			b2Vec2 targetPos(mousePos.x, mousePos.y); 
			worldDataMutex.lock();
			character->primaryFire(targetPos);
			worldDataMutex.unlock();
        }
			
		if ( pressingKeyForJumping() )
		{
			//same as above will be moved to character class
			if(released)
			{
				worldDataMutex.lock();
				character->jump();
				/*
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
					character->getBody()->ApplyLinearImpulse( b2Vec2(40, 0), character->getBody()->GetPosition() );
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
					character->getBody()->ApplyLinearImpulse( b2Vec2(-40, 0), character->getBody()->GetPosition() );
					*/
				worldDataMutex.unlock();

				released = false;
			}
		}
		else
		{
			released = true;
		}

		if ( pressingKeyForConnecting() )
		{
			//worldData->notify() bblala
			worldDataMutex.lock();
			character->connectToServer();
			worldDataMutex.unlock();
		}

		if(nullifyLinearDamping)
			character->getBody()->SetLinearDamping(0);
	}

	bool Player::pressingKeyForJumping()
	{
		return sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
	}

	bool Player::pressingKeyForPrimaryFire()
	{
		return sf::Mouse::isButtonPressed( sf::Mouse::Left );
	}

	bool Player::pressingKeyForMovingDown()
	{
		return sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
	
	}

	bool Player::pressingKeyForMovingUp()
	{
		return sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
	}

	bool Player::pressingKeyForMovingLeft()
	{
		return sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left);	
	}


	bool Player::pressingKeyForMovingRight()
	{
		return sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
	}

	bool Player::pressingKeyForConnecting()
	{
		return sf::Keyboard::isKeyPressed(sf::Keyboard::C);
	}

	void Player::moveLeft(int maxForce, int forceIteration)
	{
		worldDataMutex.lock();
		if(character->getBody()->GetLinearVelocity().x < maxForce) {
			character->getBody()->ApplyLinearImpulse( b2Vec2(float(forceIteration), 0), character->getBody()->GetPosition() );
		}
		worldDataMutex.unlock();
	}

	void Player::moveRight(int maxForce, int forceIteration)
	{
		worldDataMutex.lock();
		if(character->getBody()->GetLinearVelocity().x > -maxForce) {
			character->getBody()->ApplyLinearImpulse( b2Vec2(float(-forceIteration), 0), character->getBody()->GetPosition() );
		}
		worldDataMutex.unlock();
	}

	void Player::moveUp()
	{
		worldDataMutex.lock();
		if(character->getBody()->GetLinearVelocity().y < 10) {
			character->getBody()->ApplyLinearImpulse( b2Vec2(0, 5), character->getBody()->GetPosition() );
		}
		worldDataMutex.unlock();
	}

	void Player::moveDown()
	{
		worldDataMutex.lock();
		if(character->getBody()->GetLinearVelocity().y > -10) {
			character->getBody()->ApplyLinearImpulse( b2Vec2(0, -5), character->getBody()->GetPosition() );
		}
		worldDataMutex.unlock();
	}

}


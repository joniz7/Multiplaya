#include "Player.h"

namespace mp {
	Player::Player()
	{
		input = new Input();
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
		if( input->btnDwnLeft() || input->btnDwnRight() )
		{
			// Left movement key is pressed
			if ( input->btnDwnLeft() && !input->btnDwnRight() )	// Character should face left
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
			else if ( input->btnDwnRight() && !input->btnDwnLeft() )	// Character should face right
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
			if( !(input->btnDwnLeft() && input->btnDwnRight()) )
			{
				if ( input->btnDwnLeft() && !input->btnDwnRight() )
					if(character->isGrounded())
						moveLeft(18,50);
					else
						moveLeft(18,5);
				else if ( input->btnDwnRight() && !input->btnDwnLeft() )
					if(character->isGrounded())
						moveRight(18,50);
					else
						moveRight(18,5);

				if (input->btnDwnLeft() || input->btnDwnRight() && character->isGrounded()) {
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

		if( !(input->btnDwnLeft() || input->btnDwnRight()) && character->isGrounded() )
		{
			// Set linear damping so we stop
			character->getBody()->SetLinearDamping(10);
			character->setWalking(false);
			nullifyLinearDamping = false;
		}

		if ( input->btnDwnUp() ) 
		{
			//moveUp();
		}
		if ( input->btnDwnDown() ) 
		{
			moveDown();
		}
		if( input->btnDwnPrimary() )
        {
			b2Vec2 targetPos(mousePos.x, mousePos.y); 
			worldDataMutex.lock();
			character->primaryFire(targetPos);
			worldDataMutex.unlock();
        }
			
		if ( input->btnDwnJump() )
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


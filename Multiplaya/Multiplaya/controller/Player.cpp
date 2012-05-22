#include "Player.h"

namespace mp {
	/**
	 * Creates a new "player" instance.
	 */
	Player::Player()
	{
		input = new Input();
	}

	Player::~Player()
	{
		delete input;
	}

	/**
	 * Fetches input from the user, and updates the character according to the input.
	 * Handles walking, jumping, and anything else you can think of.
	 */
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
				//character->setIsFacingLeft(true);
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
				//character->setIsFacingLeft(false);
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
				if ( input->btnDwnLeft() && !input->btnDwnRight() ) {
					worldDataMutex.lock();
					character->moveLeft();
					worldDataMutex.unlock();
				}
				else if ( input->btnDwnRight() && !input->btnDwnLeft() ) {
					worldDataMutex.lock();
					character->moveRight();
					worldDataMutex.unlock();
				}

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

		if( (!(input->btnDwnLeft() || input->btnDwnRight())) && character->isGrounded() ) {
			// Set linear damping so we stop
			character->getBody()->SetLinearDamping(10);
			character->setWalking(false);
			nullifyLinearDamping = false;
		}

		if ( input->btnDwnUp() )
		{
			worldDataMutex.lock();
			//moveUp();
			worldDataMutex.unlock();
		}
		if ( input->btnDwnDown() )
		{
			worldDataMutex.lock();
			character->moveDown();
			worldDataMutex.unlock();
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
				worldDataMutex.unlock();

				released = false;
			}
		}
		else
		{
			released = true;
		}

		/*if ( pressingKeyForConnecting() )
		{
			//worldData->notify() bblala
			worldDataMutex.lock();
			character->connectToServer();
			worldDataMutex.unlock();
		}*/

		if ( input->btnDwnReload() )
			character->reload();

		if(nullifyLinearDamping)
			character->getBody()->SetLinearDamping(0);
	}

	bool Player::pressingKeyForConnecting()
	{
		return sf::Keyboard::isKeyPressed(sf::Keyboard::C);
	}

}


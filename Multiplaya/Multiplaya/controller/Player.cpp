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
		character->setTargetPos( b2Vec2(mousePos.x,mousePos.y) );
		character->setWallSliding(false);
		// Movement keys are pressed
		if( input->btnDwnLeft() || input->btnDwnRight() )
		{
			// Left movement key is pressed
			if ( input->btnDwnLeft() && !input->btnDwnRight() )	// Character should face left
			{
				if(character->isTouchingWallLeft())
					character->setWallSliding(true);
			}
			// Right movement key is pressed
			else if ( input->btnDwnRight() && !input->btnDwnLeft() )	// Character should face right
			{
				if(character->isTouchingWallRight())
					character->setWallSliding(true);
			}

			// If we're not trying to move in both directions at once
			if( !(input->btnDwnLeft() && input->btnDwnRight()) )
			{
				if ( input->btnDwnLeft() && !input->btnDwnRight() ) {
					character->moveLeft();
				}
				else if ( input->btnDwnRight() && !input->btnDwnLeft() ) {
					character->moveRight();
				}

				if (input->btnDwnLeft() || input->btnDwnRight() && character->isGrounded()) {
					character->setWalking(true);
				}
				else {
					character->setWalking(false);
				}
			}
		}

		if( (!(input->btnDwnLeft() || input->btnDwnRight())) && character->isGrounded() ) {
			character->setWalking(false);
		}

		if ( input->btnDwnUp() )
		{
			/*
			moveUp();
			*/
		}
		if ( input->btnDwnDown() )
		{
			character->setFloorSliding(true);
		}
		if( input->btnDwnPrimary() )
        {
			b2Vec2 targetPos(mousePos.x, mousePos.y);
			character->setFocusing(true);
			character->primaryFire(targetPos);
        }
		if( input->btnDwnSecondary() )
        {
			character->setFocusing(true);
        }
		else
		{
			character->setFocusing(false);
		}
		if ( input->btnDwnJump() )
		{
			//same as above will be moved to character class
			if(released)
			{
				character->jump();

				released = false;
			}
		}
		else
		{
			released = true;
		}

		/*if ( pressingKeyForConnecting() )
		{
			worldDataMutex.lock();
			//worldData->notify() bblala
			worldDataMutex.unlock();
			character->connectToServer();
		}*/

		if ( input->btnDwnReload() )
			character->reload();

		/*
		if(nullifyLinearDamping)
			character->getBody()->SetLinearDamping(0);
			*/
	}

	bool Player::pressingKeyForConnecting()
	{
		return sf::Keyboard::isKeyPressed(sf::Keyboard::C);
	}

}


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
		if ( pressingKeyForMovingLeft() )
		{
			moveLeft();
			character->setIsFacingLeft(true);
		}
	
		if ( pressingKeyForMovingRight() )
		{
			moveRight();
			character->setIsFacingLeft(false);
		}

		if (pressingKeyForMovingLeft() || pressingKeyForMovingRight())
		{
			character->setWalking(true);
		} 
		else {
			character->setWalking(false);
		}

		if ( pressingKeyForMovingUp() ) 
		{
			moveUp();
		}
		if ( pressingKeyForMovingDown() ) 
		{
			moveDown();
		}
		if( pressingKeyForPrimaryFire() )
        {
			b2Vec2 targetPos(mousePos.x, mousePos.y); 
			character->primaryFire(targetPos);
        }
			
		if ( pressingKeyForJumping() )
		{
			//same as above will be moved to character class
			if(released)
			{
				character->jump();
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
					character->getBody()->ApplyLinearImpulse( b2Vec2(40, 0), character->getBody()->GetPosition() );
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
					character->getBody()->ApplyLinearImpulse( b2Vec2(-40, 0), character->getBody()->GetPosition() );

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
			character->connectToServer();
		}
				
	}

	bool Player::pressingKeyForJumping()
	{
		return sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
	}

	bool Player::pressingKeyForPrimaryFire()
	{
		return sf::Mouse::isButtonPressed( sf::Mouse::Right );
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

	void Player::moveLeft()
	{
		if(character->getBody()->GetLinearVelocity().x < 7)
			character->getBody()->ApplyLinearImpulse( b2Vec2(5, 0), character->getBody()->GetPosition() );
	}

	void Player::moveRight()
	{
		if(character->getBody()->GetLinearVelocity().x > -7)
			character->getBody()->ApplyLinearImpulse( b2Vec2(-5, 0), character->getBody()->GetPosition() );
	}

	void Player::moveUp()
	{
		if(character->getBody()->GetLinearVelocity().y < 10)
			character->getBody()->ApplyLinearImpulse( b2Vec2(0, 5), character->getBody()->GetPosition() );
	}

	void Player::moveDown()
	{
		if(character->getBody()->GetLinearVelocity().y > -10)
			character->getBody()->ApplyLinearImpulse( b2Vec2(0, -5), character->getBody()->GetPosition() );
	}

}


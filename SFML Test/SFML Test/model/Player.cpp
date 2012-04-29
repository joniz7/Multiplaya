#include "Player.h"

namespace mp {
	Player::Player(WorldData* worldData, b2World* world)
	{
		this->worldData = worldData;
		this->world = world;
	}

	void Player::setCharacter(Character* character)
	{
		this->character = character;
	}

	Player::~Player()
	{
	}

	void Player::update() 
	{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				if(character->getBody()->GetLinearVelocity().x < 7)
					character->getBody()->ApplyLinearImpulse( b2Vec2(5, 0), character->getBody()->GetPosition() );
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				if(character->getBody()->GetLinearVelocity().x > -7)
					character->getBody()->ApplyLinearImpulse( b2Vec2(-5, 0), character->getBody()->GetPosition() );
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				if(character->getBody()->GetLinearVelocity().y < 10)
					character->getBody()->ApplyLinearImpulse( b2Vec2(0, 5), character->getBody()->GetPosition() );
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				if(character->getBody()->GetLinearVelocity().y > -10)
					character->getBody()->ApplyLinearImpulse( b2Vec2(0, -5), character->getBody()->GetPosition() );
			
			// Right mouse button is down
            if( sf::Mouse::isButtonPressed( sf::Mouse::Right ) )
            {
					Bullet* ba = new Bullet(BulletType::GENERIC_BULLET, 0 ,world, b2Vec2(20, 30), b2Vec2(-200, 0));
					worldData->addBullet(ba);
            }
			
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
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
				released = true;
				
	}

}


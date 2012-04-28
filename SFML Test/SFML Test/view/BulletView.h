//////////////////////////////////////////////////////////////
/// CharacterView class. Graphical representation of Character
//////////////////////////////////////////////////////////////
#ifndef BULLET_VIEW_H
#define BULLET_VIEW_H

// SFML specific headers
#include "../sfml.h"

#include "../game.h"

namespace mp
{
	class BulletView : public sf::Drawable
	{
	public:
		BulletView(Bullet* model);
		~BulletView();
	private:
		Bullet* model;
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	};
}
#endif
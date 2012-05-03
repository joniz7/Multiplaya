//////////////////////////////////////////////////////////////
/// BulletView class. Graphical representation of a bullet
//////////////////////////////////////////////////////////////
#ifndef BULLET_VIEW_H
#define BULLET_VIEW_H

// SFML specific headers
#include "../sfml.h"

#include "../game.h"

namespace mp
{
	class Bullet;

	class BulletView : public sf::Drawable
	{
	public:
		BulletView(Bullet* model);
		~BulletView();
		void updatePosition();
	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		Bullet* model;
		sf::RectangleShape* bulletVis;
	};
}
#endif
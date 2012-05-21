//////////////////////////////////////////////////////////////
/// BulletView class. Graphical representation of a bullet
//////////////////////////////////////////////////////////////
#ifndef BULLET_VIEW_H
#define BULLET_VIEW_H

// SFML specific headers
#include "../sfml.h"

#include "../global.h"
#include "GameObjectView.h"
#include "../model/bullet.h"

namespace mp
{
	class Bullet;

	class BulletView : public GameObjectView
	{
	public:
		BulletView(Bullet* model);
		virtual ~BulletView();
		void updatePosition();
	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		Bullet* model;
		sf::RectangleShape* bulletVis;
	};
}
#endif
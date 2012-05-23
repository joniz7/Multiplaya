//////////////////////////////////////////////////////////////
/// BulletView class. Graphical representation of a bullet
//////////////////////////////////////////////////////////////
#ifndef BULLET_VIEW_H
#define BULLET_VIEW_H

// SFML specific headers
#include <SFML/Graphics.hpp>

#include "../includes/Global.h"
#include "GameObjectView.h"
#include "../model/bullet.h"

namespace mp
{
	class Bullet;

	/**
	 * The visual representation of a bullet.
	 * Is tied to a Bullet, which we poll continuously
	 * for its position.
	 */
	class BulletView : public GameObjectView
	{
	public:
		BulletView(Bullet* model);
		virtual ~BulletView();
		/// Update sprite position to match bullets position
		void updatePosition();
		
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	private:
		Bullet* model;
		sf::RectangleShape* bulletVis;
	};
}
#endif
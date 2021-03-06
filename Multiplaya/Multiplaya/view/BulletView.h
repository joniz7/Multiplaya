//////////////////////////////////////////////////////////////
/// BulletView class. Graphical representation of a bullet
//////////////////////////////////////////////////////////////
#ifndef BULLET_VIEW_H
#define BULLET_VIEW_H

// SFML specific headers
#include <SFML/Graphics.hpp>

#include "../includes/Global.h"
#include "GameObjectView.h"
#include "../model/gameobjects/StandardBullet.h"

namespace mp
{
	class IBullet;

	/**
	 * The visual representation of a bullet.
	 * Is tied to a Bullet, which we poll continuously
	 * for its position.
	 */
	class BulletView : public GameObjectView
	{
	public:
		BulletView(IBullet* model);
		virtual ~BulletView();
		/// Update sprite position to match bullets position
		void update();
		
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	private:
		IBullet* model;
		sf::RectangleShape* bulletVis;
	};
}
#endif
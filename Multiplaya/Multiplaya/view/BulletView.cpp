#include "BulletView.h"

namespace mp 
{
	/**
	 * Create a new BulletView, associated to the supplied bullet.
	 * 
	 * @param model - the bullet model we're representing.
	 */
	BulletView::BulletView(Bullet* model)
	{
		this->model = model;
		bulletVis = new sf::RectangleShape( sf::Vector2f(0.25f * PIXEL_SCALE, 1.5f * PIXEL_SCALE) );
		bulletVis->setOrigin(0.125f * PIXEL_SCALE, 0.75f * PIXEL_SCALE);
		bulletVis->setFillColor(sf::Color(255, 255, 255));
		//bulletVis->setOutlineThickness(0.1f * PIXEL_SCALE);
		//bulletVis->setOutlineColor(sf::Color::Black);
	}

	/**
	 * Destructor.
	 */
	BulletView::~BulletView()
	{
		delete bulletVis;
	}

	/**
	 * Draws the bullet to the screen.
	 */
	void BulletView::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(*bulletVis, states);
	}

	/**
	 * Updates the position of this bulletView.
	 * Fetches the position and velocity from our bullet model.
	 */
	void BulletView::updatePosition()
	{
		const b2Vec2& position = model->getBody()->GetPosition();
		const b2Vec2& v = model->getBody()->GetLinearVelocity();

		float a = atan(v.x/v.y);

		bulletVis->setPosition(position.x * PIXEL_SCALE, position.y * PIXEL_SCALE);
		bulletVis->setRotation( a * 180 / -pi );
	}
}
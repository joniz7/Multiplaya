#include "BulletView.h"

namespace mp 
{

	BulletView::BulletView(Bullet* model)
	{
		this->model = model;
		bulletVis = new sf::RectangleShape( sf::Vector2f(0.5f * 1 / 10.0f, 1.5f * 1 / 10.0f) );
		bulletVis->setOrigin(0.25f * 1 / 10.0f, 0.75f * 1 / 10.0f);
		bulletVis->setFillColor(sf::Color(255, 255, 255));
		bulletVis->setOutlineThickness(0.1f * 1 / 10.0f);
		bulletVis->setOutlineColor(sf::Color::Black);
	}


	BulletView::~BulletView()
	{
		delete bulletVis;
	}

	void BulletView::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(*bulletVis, states);
	}

	void BulletView::updatePosition()
	{
		b2Vec2 position = model->getBody()->GetPosition();
		b2Vec2 v = model->getBody()->GetLinearVelocity();
		float a = atan(v.x/v.y);
		bulletVis->setPosition(position.x * 1 / 10.0f, position.y * 1 / 10.0f);
		bulletVis->setRotation( a * 180 / -pi );
	}
}
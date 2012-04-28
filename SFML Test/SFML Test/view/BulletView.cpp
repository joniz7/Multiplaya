#include "BulletView.h"

namespace mp 
{

	BulletView::BulletView(Bullet* model)
	{
		this->model = model;
	}


	BulletView::~BulletView()
	{
	}

	void BulletView::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	}
}
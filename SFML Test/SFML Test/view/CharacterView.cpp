#include "CharacterView.h"

namespace mp
{
	CharacterView::CharacterView()
	{
		//this->model = model;
		bulletVis = new sf::RectangleShape( sf::Vector2f(4.0f * (1 / 10.0f), 1.5f * (1 / 10.0f)) );
		bulletVis->setOrigin(0.25f * (1 / 10.0f), 0.75f * (1 / 10.0f));
		bulletVis->setFillColor(sf::Color(255, 255, 255));
		bulletVis->setOutlineThickness(0.1f * (1 / 10.0f));
		bulletVis->setOutlineColor(sf::Color::Black);
	}

	void CharacterView::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(*bulletVis, states);
	}

	CharacterView::~CharacterView()
	{
	}
}
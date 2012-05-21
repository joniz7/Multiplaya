#include "TextEventHelper.h"

namespace mp
{
	bool TextEventHelper::isNumber(sf::Event &textEvent)
	{
		return (textEvent.text.unicode >= 48 && textEvent.text.unicode <= 57 );
	}

	bool TextEventHelper::isBackspace(sf::Event &textEvent)
	{
		return textEvent.text.unicode == 8;
	}

	bool TextEventHelper::isDot(sf::Event &textEvent)
	{
		return textEvent.text.unicode == 46;
	}
}

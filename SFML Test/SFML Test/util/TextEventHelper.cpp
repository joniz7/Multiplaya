#include "TextEventHelper.h"

namespace mp
{
	bool TextEventHelper::isNumber(sf::Event &ev)
	{
		return (ev.text.unicode >= 48 && ev.text.unicode <= 57 );
	}

	bool TextEventHelper::isBackspace(sf::Event &ev)
	{
		return ev.text.unicode == 8;
	}

	bool TextEventHelper::isDot(sf::Event &ev)
	{
		return ev.text.unicode == 46;
	}

	void TextEventHelper::removeLastCharacter(GUIElement* element)
	{
		int textLength = element->getText().getSize();
		if (textLength > 0)
		{
			std::string text = element->getText();
			element->setText(text.erase(textLength - 1, 1));
		}
	}
}

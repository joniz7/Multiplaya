#include "TextEventHelper.h"

namespace mp
{
	/**
	 * Decides of the supplied event is a number.
	 * @returns true if number.
	 */
	bool TextEventHelper::isNumber(sf::Event &textEvent) {
		return (textEvent.text.unicode >= 48 && textEvent.text.unicode <= 57 );
	}

	/**
	 * Decides of the supplied event is a backspace.
	 * @returns true if backspace.
	 */
	bool TextEventHelper::isBackspace(sf::Event &textEvent) {
		return textEvent.text.unicode == 8;
	}

	/**
	 * Decides of the supplied event is a dot.
	 * @returns true if dot.
	 */
	bool TextEventHelper::isDot(sf::Event &textEvent) {
		return textEvent.text.unicode == 46;
	}
}

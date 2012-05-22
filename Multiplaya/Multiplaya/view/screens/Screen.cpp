#include "Screen.h"
#include <iostream>

namespace mp
{
	void Screen::setGUIElement(std::string name, GUIElement* element) 
	{
		guiElements[name] = element;
	}

	GUIElement* Screen::getGUIElement(std::string name)
	{
		return guiElements[name];
	}

	void Screen::draw(sf::RenderTarget& window, sf::RenderStates states) const 
	{
		for( std::map<std::string, GUIElement*>::const_iterator it = guiElements.begin(); it != guiElements.end(); it++ )
			window.draw(*it->second);
	}

	void Screen::hover(const sf::Vector2i& mousePos)
	{
		std::map<std::string, GUIElement*>::iterator it;
		for ( it = guiElements.begin(); it != guiElements.end(); it++)
			it->second->isMouseOver(mousePos);
	}
}
#include "Screen.h"
#include <iostream>

namespace mp
{
	/**
	* Method for accessing guielement with name provided
	* @param name
	*/
	GUIElement* Screen::getGUIElement(std::string name)
	{
		return guiElements[name];
	}

	/**
	* Method for setting guielement with name provided
	* @param name 
	* @param element - the guielement
	*/
	void Screen::setGUIElement(std::string name, GUIElement* element) 
	{
		guiElements[name] = element;
	}

	/**
	* Method for hover effects at mousepos if its elements got any
	* @param mouseposition
	*/
	void Screen::hover(const sf::Vector2i& mousePos)
	{
		std::map<std::string, GUIElement*>::iterator it;
		for ( it = guiElements.begin(); it != guiElements.end(); it++)
			it->second->isMouseOver(mousePos);
	}

	void Screen::draw(sf::RenderTarget& window, sf::RenderStates states) const 
	{
		for( std::map<std::string, GUIElement*>::const_iterator it = guiElements.begin(); it != guiElements.end(); it++ )
			window.draw(*it->second);
	}

}
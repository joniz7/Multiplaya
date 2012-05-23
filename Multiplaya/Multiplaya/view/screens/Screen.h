#ifndef SCREEN_H
#define SCREEN_H

#include <string>
#include <SFML/Graphics.hpp>
#include "../GUIElements/GUIElement.h"


using namespace guielements;
namespace mp
{
	class Screen : public sf::Drawable
	{
		public:

			/**
			* Method that updates the screen, if it contains any moving sprites or such this will be needed
			*/
			virtual void update() = 0;

			virtual void hover (const sf::Vector2i& mousePos);

			void setGUIElement(std::string name, GUIElement* element);
			GUIElement* getGUIElement(std::string name);
						
			virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;

		private:
			std::map<std::string, GUIElement*> guiElements;

	};

}
#endif // SCREEN_H

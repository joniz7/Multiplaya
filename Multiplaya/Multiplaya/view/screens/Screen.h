#ifndef SCREEN_H
#define SCREEN_H

#include <string>
#include <SFML/Graphics.hpp>
#include "../GUIElements/GUIElement.h"

namespace mp
{
	class Screen : public sf::Drawable
	{
		public:

			/// Returns element 
			/// Update the screen, if it contains any moving sprites or such this will be needed
			virtual void update() = 0;

			/// Tells screen where the mouse is for hover effects
			virtual void hover (const sf::Vector2i& mousePos);

			void setGUIElement(std::string name, GUIElement* element);
			GUIElement* getGUIElement(std::string name);
						
			virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;
		protected:
		private:
			// move this and getElement to superclass
			std::map<std::string, GUIElement*> guiElements;

	};

}
#endif // SCREEN_H

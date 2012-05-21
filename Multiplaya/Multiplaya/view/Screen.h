#ifndef SCREEN_H
#define SCREEN_H

#include <string>
#include <SFML/Graphics.hpp>

namespace mp
{

	class GUIElement;

	class Screen : public sf::Drawable
	{
		public:
			/// Returns true if mouse is hovering over any GUIElement
			virtual bool hover (const sf::Vector2i& mousePos) = 0;
			/// Returns element 
			virtual GUIElement* getElement(std::string element) = 0;
			/// Update the screen, if it contains any moving sprites or such this will be needed
			virtual void update() = 0;
		protected:
		private:
	};

}
#endif // SCREEN_H

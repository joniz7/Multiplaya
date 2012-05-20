#include "HostGameScreen.h"

namespace mp
{
	HostGameScreen::HostGameScreen(const sf::Vector2u &resolution)
	{
		font = new sf::Font();
		font->loadFromFile("resources/gothic.ttf");

		screenTitleText = new sf::Text("Host game");
		screenTitleText->setFont(*font);
		screenTitleText->setStyle(sf::Text::Bold);
		screenTitleText->setColor(sf::Color::White);
		screenTitleText->setPosition(400, 20);
		screenTitleText->setCharacterSize(40);

		ipTitleText = new sf::Text("IP: 127.0.0.1");
		ipTitleText->setFont(*font);
		ipTitleText->setStyle(sf::Text::Bold);
		ipTitleText->setColor(sf::Color::White);
		ipTitleText->setPosition(300, 100);
		ipTitleText->setCharacterSize(30);

		gravityTitleText = new sf::Text("Gravity");
		gravityTitleText->setFont(*font);
		gravityTitleText->setStyle(sf::Text::Bold);
		gravityTitleText->setColor(sf::Color::White);
		gravityTitleText->setPosition(500, 140);
		gravityTitleText->setCharacterSize(30);

		TextField* gravityTextField = new TextField(400, 100, 200, 30);
		gravityTextField->setBorderColorClicked(sf::Color::Blue);
		gravityTextField->setFontColor(sf::Color::Black);
		gravityTextField->setFontSize(20);
		gravityTextField->setBorderThicknessClicked(1);
		guiElements["gravityTextField"] = gravityTextField;

		portTitleText = new sf::Text("Port");
		portTitleText->setFont(*font);
		portTitleText->setStyle(sf::Text::Bold);
		portTitleText->setColor(sf::Color::White);
		portTitleText->setPosition(300, 140);
		portTitleText->setCharacterSize(30);

		TextField* portTextField = new TextField(400, 145, 200, 30);
		portTextField->setBorderColorClicked(sf::Color::Blue);
		portTextField->setFontColor(sf::Color::Black);
		portTextField->setFontSize(20);
		portTextField->setBorderThicknessClicked(1);	
		guiElements["portTextField"] = portTextField;

		background = new sf::RectangleShape( sf::Vector2f(float(resolution.x), float(resolution.y)) );
		background->setFillColor( sf::Color(94, 94, 94, 255) );
		background->setPosition(0, 0);

		guiElements["hostButton"] = new Button(40, 100, 200, 60, "Host game");
		guiElements["hostButton"]->setFont(*font);
		guiElements["hostButton"]->setFontColor(sf::Color::Black);

		guiElements["cancelButton"] = new Button(40, 180, 200, 60, "Cancel");
		guiElements["cancelButton"]->setFont(*font);
		guiElements["cancelButton"]->setFontColor(sf::Color::Black);
	}

	bool HostGameScreen::hover(const sf::Vector2i& mousePos)
	{
		guiElements["hostButton"]->isMouseOver(mousePos);
		guiElements["cancelButton"]->isMouseOver(mousePos);
		guiElements["gravityTextField"]->isMouseOver(mousePos);
		guiElements["portTextField"]->isMouseOver(mousePos);

		return true;
	}


	GUIElement* HostGameScreen::getElement(std::string element)
	{
		return guiElements[element];
	}

	void HostGameScreen::draw(sf::RenderTarget& window, sf::RenderStates states) const
	{
		window.draw(*background);
		window.draw(*ipTitleText);
		window.draw(*portTitleText);
		window.draw(*gravityTitleText);
		for( std::map<std::string, GUIElement*>::const_iterator it = guiElements.begin(); it != guiElements.end(); it++ )
		{
		   window.draw(*it->second);
		}
		window.draw(*screenTitleText);
	}

	HostGameScreen::~HostGameScreen()
	{
	}
}
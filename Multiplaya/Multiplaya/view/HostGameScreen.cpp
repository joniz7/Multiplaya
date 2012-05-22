#include "HostGameScreen.h"

namespace mp
{
	HostGameScreen::HostGameScreen(const sf::Vector2u &resolution)
	{
		font = new sf::Font();
		font->loadFromFile("resources/gothic.ttf");

		background = new sf::RectangleShape( sf::Vector2f(float(resolution.x), float(resolution.y)) );
		background->setFillColor( sf::Color(94, 94, 94, 255) );
		background->setPosition(0, 0);

		Button* hostButton = new Button(40, 100, 200, 60, "Host game");
		hostButton->setFont(*font);
		hostButton->setFontColor(sf::Color::Black);
		setGUIElement("hostButton", hostButton);

		Button* cancelButton = new Button(40, 180, 200, 60, "Cancel");
		cancelButton->setFont(*font);
		cancelButton->setFontColor(sf::Color::Black);
		setGUIElement("cancelButton", cancelButton);

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
		gravityTitleText->setPosition(300, 145);
		gravityTitleText->setCharacterSize(30);

		TextField* gravityTextField = new TextField(440, 145, 200, 30);
		gravityTextField->setBorderColorClicked(sf::Color::Blue);
		gravityTextField->setFontColor(sf::Color::Black);
		gravityTextField->setFontSize(20);
		gravityTextField->setBorderThicknessClicked(1);
		setGUIElement("gravityTextField", gravityTextField);

		portTitleText = new sf::Text("Port");
		portTitleText->setFont(*font);
		portTitleText->setStyle(sf::Text::Bold);
		portTitleText->setColor(sf::Color::White);
		portTitleText->setPosition(300, 200);
		portTitleText->setCharacterSize(30);

		TextField* portTextField = new TextField(440, 200, 200, 30);
		portTextField->setBorderColorClicked(sf::Color::Blue);
		portTextField->setFontColor(sf::Color::Black);
		portTextField->setFontSize(20);
		portTextField->setBorderThicknessClicked(1);	
		setGUIElement("portTextField", portTextField);

	}

	void HostGameScreen::draw(sf::RenderTarget& window, sf::RenderStates states) const
	{
		window.draw(*background);
		window.draw(*ipTitleText);
		window.draw(*portTitleText);
		window.draw(*gravityTitleText);
		window.draw(*screenTitleText);
		Screen::draw(window, states);
	}

	HostGameScreen::~HostGameScreen()
	{
	}
}
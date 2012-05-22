#include "JoinGameScreen.h"

namespace mp
{
	JoinGameScreen::JoinGameScreen(const sf::Vector2u &resolution)
	{
		font = new sf::Font();
		font->loadFromFile("resources/gothic.ttf");

		screenTitleText = new sf::Text("Connect to server");
		screenTitleText->setFont(*font);
		screenTitleText->setStyle(sf::Text::Bold);
		screenTitleText->setColor(sf::Color::White);
		screenTitleText->setPosition(400, 20);
		screenTitleText->setCharacterSize(40);

		ipTitleText = new sf::Text("IP");
		ipTitleText->setFont(*font);
		ipTitleText->setStyle(sf::Text::Bold);
		ipTitleText->setColor(sf::Color::White);
		ipTitleText->setPosition(300, 100);
		ipTitleText->setCharacterSize(30);

		TextField* ipTextField = new TextField(400, 100, 200, 30);
		ipTextField->setBorderColorClicked(sf::Color::Blue);
		ipTextField->setFontColor(sf::Color::Black);
		ipTextField->setFontSize(20);
		ipTextField->setBorderThicknessClicked(1);
		setGUIElement("ipTextField", ipTextField);


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
		setGUIElement("portTextField", portTextField);

		background = new sf::RectangleShape( sf::Vector2f(float(resolution.x), float(resolution.y)) );
		background->setFillColor( sf::Color(94, 94, 94, 255) );
		background->setPosition(0, 0);

		Button* connectButton = new Button(40, 100, 200, 60, "Connect");
		connectButton->setFont(*font);
		connectButton->setFontColor(sf::Color::Black);
		setGUIElement("connectButton", connectButton);

		Button* cancelButton = new Button(40, 180, 200, 60, "Cancel");
		cancelButton->setFont(*font);
		cancelButton->setFontColor(sf::Color::Black);
		setGUIElement("cancelButton", cancelButton);

	}

	JoinGameScreen::~JoinGameScreen()
	{
		//dtor
	}

	void JoinGameScreen::draw(sf::RenderTarget& window, sf::RenderStates states) const
	{
		window.draw(*background);
		window.draw(*ipTitleText);
		window.draw(*portTitleText);
		window.draw(*screenTitleText);
		Screen::draw(window, states);
	}
}
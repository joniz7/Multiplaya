#include "JoinGameScreen.h"

namespace mp
{
	JoinGameScreen::JoinGameScreen(const sf::Vector2u &resolution)
	{
		initBackground(resolution);
		initFont();
		initText();
		initTextFields();
		initButtons();
	}

	void JoinGameScreen::initText()
	{
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

	}

	void JoinGameScreen::initTextFields()
	{
		guielements::TextField* ipTextField = new guielements::TextField(400, 100, 200, 30);
		ipTextField->setBorderColorClicked(sf::Color::Blue);
		ipTextField->setTextColor(sf::Color::Black);
		ipTextField->setTextSize(20);
		ipTextField->setBorderThicknessClicked(1);
		setGUIElement("ipTextField", ipTextField);

	}

	void JoinGameScreen::initFont()
	{
		font = new sf::Font();
		font->loadFromFile("resources/gothic.ttf");
	}

	void JoinGameScreen::initBackground(const sf::Vector2u &resolution)
	{
		background = new sf::RectangleShape( sf::Vector2f(float(resolution.x), float(resolution.y)) );
		background->setFillColor( sf::Color(94, 94, 94, 255) );
		background->setPosition(0, 0);
	}

	void JoinGameScreen::initButtons()
	{
		Button* connectButton = new Button(40, 100, 200, 60, "Connect");
		connectButton->setFont(*font);
		connectButton->setTextColor(sf::Color::Black);
		setGUIElement("connectButton", connectButton);

		Button* cancelButton = new Button(40, 180, 200, 60, "Cancel");
		cancelButton->setFont(*font);
		cancelButton->setTextColor(sf::Color::Black);
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
		window.draw(*screenTitleText);
		Screen::draw(window, states);
	}
}
#include "JoinGameController.h"

namespace mp
{
	/**
	 * Creates a new controller for the "host game" screen.
	 * @param window the window  to tie the controller to.
	 * @param hostScreen the actual host screen we're controlling.
	 */
	JoinGameController::JoinGameController(sf::RenderWindow* window, Screen* joinGameScreen) : IController(window, joinGameScreen)
	{
		cancelButton = joinGameScreen->getGUIElement("cancelButton");
		connectButton = joinGameScreen->getGUIElement("connectButton");
		ipTextField = (TextField*) joinGameScreen->getGUIElement("ipTextField");
		portTextField = (TextField*) joinGameScreen->getGUIElement("portTextField");
	}

	JoinGameController::~JoinGameController() {}

	/**
	 * Handles input for the "join game" screen.
	 */
	void JoinGameController::handleInput()
	{
		while (getRenderWindow()->pollEvent(ev))
		{
			sf::Vector2i mousePos = sf::Mouse::getPosition(*getRenderWindow());
			// for hover effects
			getScreen()->hover(mousePos);
			if (ev.type == sf::Event::MouseButtonReleased)
			{
				clickButton(mousePos);
				selectTextField(mousePos);
			}
			if (ev.type == sf::Event::TextEntered)
				handleTextInput(ev);
		}
	}

	void JoinGameController::selectTextField(const sf::Vector2i &mousePos)
	{
		if ( ipTextField->isMouseOver(mousePos) )
		{
			// lose focus
			if (portTextField->isClicked())
				portTextField->click();

			if (ipTextField->isClicked())
				ipTextField->click();
			else
				ipTextField->click();
		}

		if ( portTextField->isMouseOver(mousePos) )
		{
			// if ipTextField is clicked then lose focus..
			if (ipTextField->isClicked())
				ipTextField->click();

			if (portTextField->isClicked())
				portTextField->click();
			else
				portTextField->click();
		}
	}

	void JoinGameController::clickButton(const sf::Vector2i &mousePos)
	{
		if( connectButton->isMouseOver(mousePos) )
		{
			connectButton->click();
			networkHandler->connectToServer("Jonte", "129.16.187.42");

			clock.restart();
			float elapsed = clock.getElapsedTime().asSeconds();
			while(!networkHandler->isConnectedToServer() && elapsed < 3)
				elapsed = clock.getElapsedTime().asSeconds();

			if(networkHandler->isConnectedToServer())
			{
				//networkHandler->setIPAddress(ipTextField->getText());
				networkHandler->setAsClient();
				// Change screen in main controller.
				notifyObservers(START_GAME, 0);
			}
		}

		if ( cancelButton->isMouseOver(mousePos) )
		{
			cancelButton->click();
			notifyObservers(SHOW_MAIN_MENU, 0);
		}
	} // end of clickButton

	
	void JoinGameController::handleTextInput(sf::Event &textEvent)
	{
		if (TextEventHelper::isNumber(ev))
		{
			if (ipTextField->isClicked())
				ipTextField->setText(ipTextField->getText() + ev.text.unicode);
			if (portTextField->isClicked())
				portTextField->setText(portTextField->getText() + ev.text.unicode);
		}
		else if (TextEventHelper::isDot(ev))
		{
			// TODO "remove" the possibility to input double dots
			if (ipTextField->isClicked())
				ipTextField->setText(ipTextField->getText() + ev.text.unicode);
		}
		else if (TextEventHelper::isBackspace(ev))
		{
			if (ipTextField->isClicked())
				ipTextField->removeLastCharacter();
			if (portTextField->isClicked())
				portTextField->removeLastCharacter();
		}
	}
}

#include "JoinGameController.h"

namespace mp
{
	JoinGameController::JoinGameController(sf::RenderWindow* window, Screen* joinGameScreen) : IController(window, joinGameScreen)
	{
		cancelButton = joinGameScreen->getElement("cancelButton");
		connectButton = joinGameScreen->getElement("connectButton");
		ipTextField = joinGameScreen->getElement("ipTextField");
		portTextField = joinGameScreen->getElement("portTextField");

		ipTextClicked = false;
		portTextClicked = false;

	}

	JoinGameController::~JoinGameController()
	{
		//dtor
	}

	void JoinGameController::handleInput()
	{
		// for hover effects
		while (getRenderWindow()->pollEvent(ev))
		{
			sf::Vector2i mousePos = sf::Mouse::getPosition(*getRenderWindow());
			getScreen()->hover(mousePos);

			if (ev.type == sf::Event::MouseButtonReleased)
			{
				// get in constructor instead
				if ( cancelButton->isMouseOver(mousePos) )
				{
					cancelButton->click();
					GameState::getInstance()->setGameState(GameState::MAIN_SCREEN);
				}

				if ( ipTextField->isMouseOver(mousePos) )
				{
					// lose focus
					if (portTextClicked)
					{
						portTextField->click();
						portTextClicked = false;
					}

					if (ipTextClicked)
					{
						ipTextField->click();
						ipTextClicked = false;
					}
					else
					{
						ipTextField->click();
						ipTextClicked = true;
					}

				}

				if ( portTextField->isMouseOver(mousePos) )
				{
					// lose focus
					if (ipTextClicked)
					{
						ipTextField->click();
						ipTextClicked = false;
					}

					if (portTextClicked)
					{
						portTextField->click();
						portTextClicked = false;
					}
					else
					{
						portTextField->click();
						portTextClicked = true;
					}

				}
			}

			if (ev.type == sf::Event::TextEntered)
			{
				if (isNumberOrDot(ev))
				{
					if (ipTextClicked)
						ipTextField->setText(ipTextField->getText() + ev.text.unicode);
					if (portTextClicked)
						portTextField->setText(portTextField->getText() + ev.text.unicode);
				}

					//event.TextEvent.unicode;
					//char c = static_cast<char>();

					// sf::Event::TextEvent::unicode;
						//if ipfield is clicked, set text in that field

					//if portfield is clicked, set text in that field
			}

		}

	}

	bool JoinGameController::isNumberOrDot(sf::Event &ev)
	{
		return (ev.text.unicode >= 48 && ev.text.unicode <= 57 ) || ev.text.unicode == 46;
	}
}
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
// Class header
#include "input.h"

////////////////////////////////////////////////////////////
/// Class description
////////////////////////////////////////////////////////////

namespace mp	
{
	////////////////////////////////////////////////////////////
	// Constructor
	////////////////////////////////////////////////////////////
    Input::Input()
    {
		keyLib = new KeyLookup();

		btnLeft = keyLib->getKey( ConfigHandler::instance().getString("b_moveleft") );
		btnRight = keyLib->getKey( ConfigHandler::instance().getString("b_moveright") );
		btnUp = keyLib->getKey( ConfigHandler::instance().getString("b_crouch") );

		std::cout<<"AJE "<<ConfigHandler::instance().getString("b_jump")<<std::endl;

		std::cout<<"Hejhej "<<ConfigHandler::instance().getString("b_primaryfire");

		btnJump = keyLib->getKey( ConfigHandler::instance().getString("b_jump") );
		btnPrimary = keyLib->getMouseButton( ConfigHandler::instance().getString("b_primaryfire") );
		btnSecondary = keyLib->getMouseButton( ConfigHandler::instance().getString("b_secondaryfire") );

    }

	////////////////////////////////////////////////////////////
	// Destructor
	////////////////////////////////////////////////////////////
    Input::~Input()
    {

    }
}

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
		// Keyboard keys
		btnLeft = keyLib->getKey( ConfigHandler::instance().getString("b_moveleft") );
		btnRight = keyLib->getKey( ConfigHandler::instance().getString("b_moveright") );
		btnUp = keyLib->getKey( ConfigHandler::instance().getString("b_crouch") );
		btnJump = keyLib->getKey( ConfigHandler::instance().getString("b_jump") );
		// Mouse buttons
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

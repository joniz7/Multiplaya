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
	/**
	 * Creates a new instance of the Input class.
	 * Loads keys from the config file.
	 */
    Input::Input()
    {
		keyLib = new KeyLookup();
		// Keyboard keys
		btnLeft = keyLib->getKey( ConfigHandler::instance().getString("b_moveleft") );
		btnRight = keyLib->getKey( ConfigHandler::instance().getString("b_moveright") );
		btnUp = keyLib->getKey( ConfigHandler::instance().getString("b_crouch") );
		btnJump = keyLib->getKey( ConfigHandler::instance().getString("b_jump") );
		btnReload = keyLib->getKey( ConfigHandler::instance().getString("b_reload") );
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

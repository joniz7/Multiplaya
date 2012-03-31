////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
// Class header
#include "resourcehandler.h"
#include "confighandler.h"

////////////////////////////////////////////////////////////
/// Class for managing loading and distribution of resources
/// such as textures, sounds etc.
////////////////////////////////////////////////////////////

namespace mp	
{
	////////////////////////////////////////////////////////////
	// Constructor
	////////////////////////////////////////////////////////////
    ResourceHandler::ResourceHandler()
    {
		// Set default values
		doRtLoading = ConfigHandler::getInstance().getBool("realtimeloading");
    }

	////////////////////////////////////////////////////////////
	// Destructor
	////////////////////////////////////////////////////////////
    ResourceHandler::~ResourceHandler(){}

	/*
	////////////////////////////////////////////////////////////
	// Loads several textures from a string vector
	////////////////////////////////////////////////////////////
    void ResourceHandler::loadTextures(std::string filePath)
    {
	}
	*/

	////////////////////////////////////////////////////////////
	// Load a texture to memory. Returns true upon success
	////////////////////////////////////////////////////////////
    bool ResourceHandler::loadTexture(std::string filePath)
    {
		// Check if file already has been loaded
		for( std::map<std::string,sf::Texture>::iterator it=texMap.begin(); it!=texMap.end(); ++it)
		   if( (*it).first.compare(filePath)  )
			   return true;
		// Attempt to load from file
		sf::Texture temp;
		if(!temp.loadFromFile(filePath))
			return false;
		else
		{
			texMap[filePath] = temp;
			return true;
		}
    }

	////////////////////////////////////////////////////////////
	// Fetches a texture pointer. If texture is not present in
	// memory and doRtLoading is set to true, attempt to load
	// the texture.
	////////////////////////////////////////////////////////////
	sf::Texture* ResourceHandler::getTexture(std::string filePath)
    {
		// Check if file exists in memory
		for( std::map<std::string,sf::Texture>::iterator it=texMap.begin(); it!=texMap.end(); ++it)
			if( (*it).first.compare(filePath)  )
				return &texMap[filePath];	// It did, return pointer
			else if(doRtLoading) // If not, check if we are allowing real time loading
				if (loadTexture(filePath)); // If so, attempt to load texture
					return getTexture(filePath); // Upon success try to get pointer again (be aware that if loadTexture does not function correctly this may get stuck in a loop)
    }
}

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
// Class header
#include "resourcehandler.h"



namespace mp
{

	/**
	 * Returns a pointer to the singleton.
	 */
    ResourceHandler& ResourceHandler::instance()
    {
		static ResourceHandler instance;
		return instance;
    }

	/**
	 * Constructor. Creates a new resource handler.
	 */
    ResourceHandler::ResourceHandler()
    {
		// Set default values
		doRtLoading = ConfigHandler::instance().getBool("s_realtimeloading");
		sf::Texture tempTex;
		sf::SoundBuffer tempSound;
		// Load debug textures
		loadTexture("resources/debug/missingtexture.png");
		loadSound("resources/debug/missingsound.wav");
		/*
		if(tempTex.loadFromFile("resources/debug/missingtexture.png"))
			texMap["resources/debug/missingtexture.png"] = tempTex;

		if(tempSound.loadFromFile("resources/debug/missingsound.wav"))
			soundMap["resources/debug/missingsound.wav"] = tempSound;
		*/
    }

	/** 
	 * Loads a texture to memory.
	 * @returns true upon success.
	 */
    bool ResourceHandler::loadTexture(std::string filePath)
    {
		// Check if file already has been loaded
		for( std::map<std::string,sf::Texture>::iterator it=texMap.begin(); it!=texMap.end(); ++it)
		   if( (*it).first == (filePath)  )
			   return true;

		std::cout<<"Loading "<<filePath<<std::endl;
		// Attempt to load from file
		sf::Texture temp;
		if(!temp.loadFromFile(filePath))
		{
			std::cout<<"Loading "<<filePath<<" FAILED."<<std::endl;
			return false;
		}
		else
		{
			texMap[filePath] = temp;

			// For some FUCKING reason we have to load another textore or else the one we just loaded won't work. TODO: FIX THIS SHIT
			//if(temp.loadFromFile("resources/debug/missingtexture.png"))
			//	texMap["resources/debug/missingtexture.png"] = temp;

			return true;
		}
    }

	/** 
	 * Loads a sound to memory.
	 * @returns true upon success.
	 */
    bool ResourceHandler::loadSound(std::string filePath)
    {
		// Check if file already has been loaded
		for( std::map<std::string,sf::SoundBuffer>::iterator it=soundMap.begin(); it!=soundMap.end(); ++it)
		   if( (*it).first == (filePath)  )
			   return true;

		std::cout<<"Loading "<<filePath<<std::endl;
		// Attempt to load from file
		sf::SoundBuffer temp;
		if(!temp.loadFromFile(filePath))
		{
			std::cout<<"Loading "<<filePath<<" FAILED."<<std::endl;
			return false;
		}
		else
		{
			soundMap[filePath] = temp;

			return true;
		}
    }

	/**
	 * Given a string vector, loads several textures.
	 */
    void ResourceHandler::loadTextures(std::vector<std::string> pathVec)
    {
		// Iterate through vector and load all files
		for (unsigned int i=0; i<pathVec.size(); i++)
			loadTexture(pathVec[i]);
	}

	/**
	 * Fetches a texture pointer. If texture is not present in
	 * memory and doRtLoading is set to true, attempt to load
	 * the texture.
	 */
	sf::Texture* ResourceHandler::getTexture(std::string filePath)
    {
		// Check if file exists in memory
		for( std::map<std::string,sf::Texture>::iterator it=texMap.begin(); it!=texMap.end(); ++it)
		{
			//std::cout<<(*it).first<<" = "<<filePath<<std::endl;
			if( (*it).first == filePath )
				return &texMap[filePath];	// It did, return pointer
		}
		if(doRtLoading) // If not, check if we are allowing real time loading
		{
			std::cout<<"Texture "<<filePath<<" not found in memory, attempting to load..."<<std::endl;
			if( loadTexture(filePath) );
				return &texMap[filePath];
		}
		else
		{
			std::cout<<"Texture "<<filePath<<" not found in memory."<<std::endl;
			return &texMap["resources/debug/missingtexture.png"];
		}
    }

	/**
	 * Fetches a sound pointer. If sound is not present in
	 * memory and doRtLoading is set to true, attempt to load
	 * the sound.
	 */
	sf::SoundBuffer* ResourceHandler::getSound(std::string filePath)
    {
		// Check if file exists in memory
		for( std::map<std::string,sf::SoundBuffer>::iterator it=soundMap.begin(); it!=soundMap.end(); ++it)
		{
			//std::cout<<(*it).first<<" = "<<filePath<<std::endl;
			if( (*it).first == filePath )
				return &soundMap[filePath];	// It did, return pointer
		}
		if(doRtLoading) // If not, check if we are allowing real time loading
		{
			std::cout<<"Sound "<<filePath<<" not found in memory, attempting to load..."<<std::endl;
			if( loadTexture(filePath) );
				return &soundMap[filePath];
		}
		else
		{
			std::cout<<"Sound "<<filePath<<" not found in memory."<<std::endl;
			return &soundMap["resources/debug/missingsound.wav"];
		}
    }

	/**
	 * Reloads a texture stored in memory.
	 * @returns true upon success.
	 */
	bool ResourceHandler::reloadTexture(std::string filePath)
    {
		// Check if file exists in memory
		for( std::map<std::string,sf::Texture>::iterator it=texMap.begin(); it!=texMap.end(); ++it)
			if( (*it).first.compare(filePath)  )
			{
				(*it).second.loadFromFile((*it).first);	// It did, let's reload it
				return true;
			}
		return false;	// It didn't
    }

	/**
	 * Reloads all textures stored in memory.
	 */
	void ResourceHandler::reloadAllTextures()
    {
		// Iterate through map and reload every texture
		for( std::map<std::string,sf::Texture>::iterator it=texMap.begin(); it!=texMap.end(); ++it)
			(*it).second.loadFromFile((*it).first);
    }

	/**
	 * Reloads all sounds stored in memory.
	 */
	void ResourceHandler::reloadAllSounds()
    {
		// Iterate through map and reload every texture
		for( std::map<std::string,sf::SoundBuffer>::iterator it=soundMap.begin(); it!=soundMap.end(); ++it)
			(*it).second.loadFromFile((*it).first);
    }
}

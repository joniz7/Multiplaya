////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
// Class header
#include "MusicHandler.h"

#include<iostream>
#include<iomanip>
#include<fstream>
#include<algorithm>


////////////////////////////////////////////////////////////
/// Singleton class for handling music playback.
////////////////////////////////////////////////////////////

namespace mp	
{

	////////////////////////////////////////////////////////////
	// Returns a pointer to the singleton.
	////////////////////////////////////////////////////////////
    MusicHandler& MusicHandler::instance()
    {
		static MusicHandler instance;
		return instance;
    }

	////////////////////////////////////////////////////////////
	/// Constructor. Loads settings from config,
	///               and loads music files from filesystem.
	////////////////////////////////////////////////////////////
	MusicHandler::MusicHandler() {
		// Fetch settings from config.
		titleMusicEnabled = ConfigHandler::instance().getBool("m_titlemusicenabled");
		bgMusicEnabled = ConfigHandler::instance().getBool("m_bgmusicenabled");
		titleMusicPitch = ConfigHandler::instance().getFloat("m_titlemusicpitch");
		bgMusicPitch = ConfigHandler::instance().getFloat("m_bgmusicpitch");
		titleMusicVolume = ConfigHandler::instance().getFloat("m_titlemusicvolume");
		bgMusicVolume = ConfigHandler::instance().getFloat("m_titlemusicvolume");

		// Nothing is currently playing.
		currentlyPlaying = NULL;

		std::string resourcesDir = "resources/";

		// Load title music.
		if (titleMusicEnabled) {
			sf::Music* titleMusic = new sf::Music();
			if (!titleMusic->openFromFile(resourcesDir+"music/title.ogg")) {
				std::cout << "MusicHandler: loading of title.ogg failed!" << std::endl;
			}
			titleMusic->setPitch(titleMusicPitch);
			titleMusic->setVolume(titleMusicVolume);
			titleMusic->setLoop(true);
			std::cout << "playSong() 1" << std::endl;
			songs.insert(std::pair<std::string,sf::Music*>("title",titleMusic) );
			std::cout << "playSong() 2!" << std::endl;
		}
		// Load in-game music.
		if (bgMusicEnabled) {
			sf::Music* bgMusic = new sf::Music();
			if (!bgMusic->openFromFile(resourcesDir+"music/bg.ogg")) {
				std::cout << "MusicHandler: loading of bg.ogg failed!" << std::endl;
			}
			bgMusic->setPitch(bgMusicPitch);
			bgMusic->setVolume(bgMusicVolume);
			bgMusic->setLoop(true);
			songs.insert(std::pair<std::string,sf::Music*>("bg",bgMusic) );
		}
		
	}

	//////////////////////////////////////
	/// Play the current song.
	//////////////////////////////////////
	void MusicHandler::play() {
		// If we have chosen a song,
		if (currentlyPlaying != NULL) {
			// Play it.
			currentlyPlaying->play();
		}
	}

	//////////////////////////////////////
	/// Pause the current song.
	//////////////////////////////////////
	void MusicHandler::pause() {
		// If we have chosen a song,
		if (currentlyPlaying != NULL) {
			// Pause it.
			currentlyPlaying->pause();
		}
	}

	//////////////////////////////////////
	/// Play the song with the given name.
	//////////////////////////////////////
	void MusicHandler::chooseSong(std::string name) {
		// If the name exists in map,
		if(songs.find(name) != songs.end()) {
			// stop currently playing song (if any),
			if (currentlyPlaying != NULL) {
				currentlyPlaying->stop();
			}
			// and choose the new song.
			currentlyPlaying = songs.at(name);
		}
	}

	MusicHandler::~MusicHandler() {

		currentlyPlaying = NULL;

		// Delete all sf::Music's.
		std::map<std::string,sf::Music*>::iterator it;
		for(it = songs.begin();it!=songs.end();it++) {
			delete (*it).second;
		}

	}
}

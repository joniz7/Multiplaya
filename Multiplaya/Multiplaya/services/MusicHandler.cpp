// Class header
#include "MusicHandler.h"

#include<iostream>
#include<iomanip>
#include<fstream>
#include<algorithm>

namespace mp	
{

	/**
	 * Returns a pointer to the singleton.
	 */
    MusicHandler& MusicHandler::instance() {
		static MusicHandler instance;
		return instance;
    }

	/** 
	 * Constructor. Loads settings from config,
	 * and loads music files from filesystem.
	 */
	MusicHandler::MusicHandler() {
		// Fetch settings from config.
		menuMusicEnabled = ConfigHandler::instance().getBool("m_menumusicenabled");
		bgMusicEnabled = ConfigHandler::instance().getBool("m_bgmusicenabled");
		menuMusicPitch = ConfigHandler::instance().getFloat("m_menumusicpitch");
		bgMusicPitch = ConfigHandler::instance().getFloat("m_bgmusicpitch");
		menuMusicVolume = ConfigHandler::instance().getFloat("m_menumusicvolume");
		bgMusicVolume = ConfigHandler::instance().getFloat("m_bgmusicvolume");

		// Nothing is currently playing.
		currentlyPlaying = NULL;

		std::string resourcesDir = "resources/";

		// Load menu music.
		if (menuMusicEnabled) {
			sf::Music* menuMusic = new sf::Music();
			if (!menuMusic->openFromFile(resourcesDir+"music/menu.ogg")) {
				std::cout << "MusicHandler: loading of menu.ogg failed!" << std::endl;
			}
			menuMusic->setPitch(menuMusicPitch);
			menuMusic->setVolume(menuMusicVolume);
			menuMusic->setLoop(true);
			songs.insert(std::pair<std::string,sf::Music*>("menu",menuMusic) );
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

	/**
	 * Play the current song.
	 */
	void MusicHandler::play() {
		// If we have chosen a song,
		if (currentlyPlaying != NULL) {
			// Play it.
			currentlyPlaying->play();
		}
	}

	/**
	 * Pause the current song.
	 */
	void MusicHandler::pause() {
		// If we have chosen a song,
		if (currentlyPlaying != NULL) {
			// Pause it.
			currentlyPlaying->pause();
		}
	}

	/**
	 * Select the song with the given name.
	 */
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

	/**
	 * Destructor. Destroys all created music objects.
	 */
	MusicHandler::~MusicHandler() {

		currentlyPlaying = NULL;

		// Delete all sf::Music's.
		std::map<std::string,sf::Music*>::iterator it;
		for(it = songs.begin();it!=songs.end();it++) {
			delete (*it).second;
		}

	}
}

////////////////////////////////////////////////////////////
/// Class description
////////////////////////////////////////////////////////////
#ifndef MUSICHANDLER_H_INCLUDED
#define MUSICHANDLER_H_INCLUDED

#include "../sfml.h"
#include "confighandler.h"

// Other headers
#include <string>
#include <cstdlib>
#include <list>
#include <cmath>
#include <map>
#include <iterator>

namespace mp
{
    class MusicHandler {
        public:
			static MusicHandler& instance();
			void chooseSong(std::string name);
			void play();
			void pause();

        private:
			// Singleton stuff
			MusicHandler();
			~MusicHandler();
			MusicHandler(MusicHandler const&){};
			MusicHandler& operator=(MusicHandler const&);
			// All available songs.
			std::map<std::string, sf::Music*> songs;
			// Currently playing song.
			sf::Music* currentlyPlaying;
			// Settings.
			bool menuMusicEnabled;
			bool bgMusicEnabled;

			float menuMusicPitch;
			float bgMusicPitch;
			float menuMusicVolume;
			float bgMusicVolume;
    };
}

#endif

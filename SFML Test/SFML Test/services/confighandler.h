////////////////////////////////////////////////////////////
/// Class description
////////////////////////////////////////////////////////////
#ifndef CONFIGHANDLER_H_INCLUDED
#define CONFIGHANDLER_H_INCLUDED

// Other headers
#include <string>
#include <cstdlib>
#include <list>
#include <cmath>
#include <map>

namespace mp
{
    class ConfigHandler
    {
        public:
			static ConfigHandler& instance();
			bool getBool(std::string s) {return boolMap[s];};
			int getInt(std::string s) {return intMap[s];};
			float getFloat(std::string s) {return floatMap[s];};
			std::string getString(std::string s) {return stringMap[s];};
        private:
			// Singleton stuff
			ConfigHandler();
			ConfigHandler(ConfigHandler const&){};
			ConfigHandler& operator=(ConfigHandler const&){};
			// Data maps
			std::map<std::string, bool> boolMap;
			std::map<std::string, int> intMap;
			std::map<std::string, float> floatMap;
			std::map<std::string, std::string> stringMap;
			// Other
			std::string configPath;
    };
}

#endif

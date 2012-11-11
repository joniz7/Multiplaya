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
	/**
	 * A singleton class, which reads data from a configuration file
	 * and stores it in a map for easy access from anywhere in the program. Should not be read in real-time since it does string comparision!
	 */
    class ConfigHandler
    {
        public:
			static ConfigHandler& instance();
			/// Returns the boolean value associated whith the inputted string.
			bool getBool(std::string s) {return boolMap[s];};
			/// Returns the integer value associated whith the inputted string.
			int getInt(std::string s) {return intMap[s];};
			/// Returns the floating point value associated whith the inputted string.
			float getFloat(std::string s) {return floatMap[s];};
			/// Returns the string value associated whith the inputted string.
			std::string getString(std::string s) {return stringMap[s];};
        private:
			// Singleton stuff
			ConfigHandler();
			ConfigHandler(ConfigHandler const&){};
			ConfigHandler& operator=(ConfigHandler const&);
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

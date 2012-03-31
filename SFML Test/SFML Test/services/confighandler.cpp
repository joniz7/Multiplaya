////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
// Class header
#include "confighandler.h"

#include<iostream>
#include<iomanip>
#include<fstream>
#include<algorithm>


////////////////////////////////////////////////////////////
/// Reads config file and stores data in a map. Singleton.
////////////////////////////////////////////////////////////

namespace mp	
{
	////////////////////////////////////////////////////////////
	// Returns a pointer to the singleton
	////////////////////////////////////////////////////////////
    ConfigHandler& ConfigHandler::getInstance()
    {
		static ConfigHandler instance;
		return instance;
    }

	////////////////////////////////////////////////////////////
	// Constructor. Loads the config file and saves settings to
	// memory.
	////////////////////////////////////////////////////////////
	ConfigHandler::ConfigHandler()
	{
		configPath="config.cfg";
		std::ifstream fileReader;
		fileReader.open(configPath.c_str());
        if(!fileReader)
        {
            std::cout<<"Unable to open config.cfg. Creating new file with default values."<<std::endl;
			//TODO: Create default cfg file
        }
		else
		{
			std::string line;
			while(getline(fileReader,line))
            {
				if(!line.empty()&&line.find("=")!=std::string::npos)
				{
					// Trim whitespace
					line.erase( remove( line.begin(), line.end(), ' ' ), line.end() );
					// Trim tabs
					line.erase( remove( line.begin(), line.end(), '\t' ), line.end() );
					// Split string
					int splitter = line.find("=");
					std::string setting = line.substr(0,splitter);
					std::string data = line.substr(setting.length()+1,std::string::npos);
					//std::cout<<setting<<": "<<data;
					// Convert to lower case
					for(int i=0;i<setting.length();++i)
						setting[i] = ::tolower(setting[i]);
					for(int i=0;i<data.length();++i)
						data[i] = ::tolower(data[i]);

					// Determine which map to store the data in
					if(data == "true")	// Bool
						boolMap[setting] = true;
					else if(data == "false")	// Bool
						boolMap[setting] = false;
					else if(data.find(".")!=std::string::npos)
						floatMap[setting] = atof(data.c_str());	// Float
					else
						intMap[setting] = atoi(data.c_str());	// Int
				}
            }
			std::cout<<"Config file read!"<<std::endl;
		}

		fileReader.close();

	}

}

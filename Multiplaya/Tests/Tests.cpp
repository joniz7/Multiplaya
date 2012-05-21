// Tests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "gtest/gtest.h"

//#include <global.h>
#include <sfml.h>
#include <model/worlddata.h>

// Define worldData ^__^
mp::WorldData* worldData;
b2World* physicsWorld;


int _tmain(int argc, _TCHAR* argv[])
{
	testing::InitGoogleTest(&argc, argv); 
    RUN_ALL_TESTS(); 
    std::getchar(); // keep console window open until Return keystroke

	return 0;
}
// Tests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "gtest/gtest.h"

#include "../SFML Test/model/worlddata.h"
#include "../SFML Test/global.h"
#include "../SFML Test/sfml.h"

TEST(sample_test_case, sample_test)
{
    EXPECT_EQ(1, 1);
}


int _tmain(int argc, _TCHAR* argv[])
{
	testing::InitGoogleTest(&argc, argv); 
    RUN_ALL_TESTS(); 
    std::getchar(); // keep console window open until Return keystroke

	return 0;
}
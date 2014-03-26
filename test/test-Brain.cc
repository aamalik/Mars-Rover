/**
 * @file test-Brain
 * @brief Test cases for the Brain
 */ 

#include <string>
#include "test-Brain.h"
#include "Brain.hh"

using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION(BrainTest);

void BrainTest::setUp(){

  this->brain = new Brain(code);  
}

void BrainTest::tearDown(){

  delete brain;
}

void BrainTest::testInitBrain(){

  string data[] = {"T 1000.00 -- 112.000 113.000 114.000 115.000 b 6.000 7.000 8.000 m 9.000 8.000 10.000 11.000 c 12.000 13.000 14.000;",
		   "T 1000.00 al 112.000 113.000 114.000 115.000 b 6.000 7.000 8.000 m 9.000 8.000 10.000 11.000 c 12.000 13.000 14.000;"
  };

  for(int i=0;i<2;i++)
    CPPUNIT_ASSERT(this->brain->initializeMemory(data[i]) == 0);  
}

void BrainTest::testParseData(){

  string data[] = {"T 1000.00 -- 112.000 113.000 114.000 115.000 b 6.000 7.000 8.000 m 9.000 8.000 10.000 11.000 c 12.000 13.000 14.000;",
		   "T 1000.00 al 112.000 113.000 114.000 115.000 b 6.000 7.000 8.000 m 9.000 8.000 10.000 11.000 c 12.000 13.000 14.000;"
  };

  for(int i=0;i<2;i++)
    CPPUNIT_ASSERT(this->brain->parseData(data[i]) == 0);
}



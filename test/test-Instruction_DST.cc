/**
 * @file test-Instruction_GAP
 * @brief Test cases for the Instruction_GAP
*/ 

#include <vector>
#include <string>
#include <math.h>
#include <cstdlib>
#include <sstream>

#include "test-Instruction_DST.h"
#include "Instruction_DST.hh"

using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION(InstructionDSTTest);

void InstructionDSTTest::setUp(){

}

void InstructionDSTTest::tearDown(){

}

void InstructionDSTTest::testDST(){

  for(int i=0;i<20;i++){
    
    MemoryHandler mem;
    stringstream init;

    double x1 = rand() % 50;
    double x2 = rand() % 50;
    double y1 = rand() % 50;
    double y2 = rand() % 50;    

    init << "T 1000.00 -- 112.000 113.000 114.000 115.000 ";
    init << "m " << x1 << " " << y1 << " " << 0.0 << " " << 0.0 << " ";
    init << "m " << x2 << " " << y2 << " " << 0.0 << " " << 0.0 << ";";
    
    mem.parseData(init.str());

    vector<string> args;
    args.push_back("result");
    args.push_back("Martian[0]");
    args.push_back("Martian[1]");

    double dist = sqrt(pow(x1-x2,2) + pow(y1-y2,2));

    int argc = 3;
    int ip = 0;
    Instruction_DST dst(&argc,args);

    CPPUNIT_ASSERT(dst.execute(&mem,&ip) == 0);    
    CPPUNIT_ASSERT(ip == 0);

    double res = 0;
    mem.getValue(&res,"result");
    
    CPPUNIT_ASSERT(res + 0.001 >= dist &&
		   res - 0.001 <= dist);
  }
}




/**
 * @file test-Instruction_GAP
 * @brief Test cases for the Instruction_GAP
 */ 

#include <vector>
#include <string>
#include <math.h>
#include <cstdlib>
#include <sstream>

#include "test-Instruction_GTA.h"
#include "Instruction_GTA.hh"
#include "Position.hh"

#define PI 3.14159265

using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION(TestInstructionGTA);

void TestInstructionGTA::setUp(){}

void TestInstructionGTA::tearDown(){}

double TestInstructionGTA::calcAngle(Position p){

  double angle = atan2( p.getY(), p.getX() ) * 180 / PI;
  return angle;
}

void TestInstructionGTA::testInstructionGTA(){

  for(int i=0;i<9;i++){

    MemoryHandler mem;
    vector<string> args;
    args.push_back("result");
    args.push_back("thePosition");

    Position p(rand() % 50,rand() % 50);
    double angle = this->calcAngle(p);
    mem.setValue(&p,POSITION,"thePosition");
    int argc = 2;
    int ip = 0;

    Instruction_GTA gta(&argc,args);

    CPPUNIT_ASSERT(gta.execute(&mem,&ip) == 0);
    CPPUNIT_ASSERT(ip == 0);

    double result = 0;
    
    mem.getValue(&result,"result");

    CPPUNIT_ASSERT(result + 0.001 >= angle &&
		   result - 0.001 <= angle);
    
  }
}



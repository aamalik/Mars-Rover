/**
 * @file test-Instruction_SIM
 * @brief Test cases for the Instruction_SIM
 */ 

#include <math.h>

#include "Position.hh"
#include "ArgumentType.hh"
#include "MemoryHandler.hh"
#include "test-Instruction_SIM.h"
#include "Instruction_SIM.hh"

CPPUNIT_TEST_SUITE_REGISTRATION(TestInstructionSIM);

void TestInstructionSIM::setUp(){
}

void TestInstructionSIM::tearDown(){

  
}

Position TestInstructionSIM::calculatePosition(SpaceObject obj,int time,double speed){

  Position pos(0,0);
  double heading;

  obj.getValue(&pos,"Position");
  obj.getValue(&heading,"Heading");

  pos.setX(pos.getX() + speed*cos(heading)*time);
  pos.setY(pos.getY() + speed*sin(heading)*time);

  return pos;
}

void TestInstructionSIM::testInstructionSIM(){

  double PI = atan(1.0)*4;
  

  for(int i = 0; i<= 360;i++){

    double x = rand() % 50;
    double y = rand() % 50;
    double speed = rand() % 10;
    double heading = i*PI/180;
    int time = rand() % 10;
    int ip = 0;
    stringstream s,m;
    s << time;
    m << "T 1000.00 -- 112.000 113.000 114.000 115.000 " << "m " << x << " " << y << " " << speed << " " << heading << ";";
    SpaceObject kaiser(x,y,1,speed,heading);
    MemoryHandler mem;

    mem.parseData(m.str());
    mem.setValue(&ip,INT,"theIndex");
    mem.getValue(&kaiser,"Martian[theIndex]");

    int argc = 3;
    vector<string> args;

    args.push_back("result");
    args.push_back(s.str());
    args.push_back("Martian[theIndex]");

    Instruction_SIM sim(&argc,args);
    sim.execute(&mem,&ip);

    CPPUNIT_ASSERT(ip == 0);

    Position res(0,0);
    Position pos = this->calculatePosition(kaiser,time,speed);

    mem.getValue(&res,"result");

    CPPUNIT_ASSERT(res.getX() + 0.001 >= pos.getX() &&
                   res.getX() - 0.001 <= pos.getX() &&
		   res.getY() + 0.001 >= pos.getY() &&
                   res.getY() - 0.001 <= pos.getY());
  }
}



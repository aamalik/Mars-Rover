/**
 * @file test-Instruction_GAP
 * @brief Test cases for the Instruction_GAP
*/ 

#include <vector>
#include <string>
#include <math.h>
#include <cstdlib>
#include <sstream>

#include "test-Instruction_GAP.h"
#include "Instruction_GAP.hh"

using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION(InstructionGAPTest);

void InstructionGAPTest::createAllPossibilities(map<string,Position> &positions,SpaceObject obj,int time, double maxTurn, double maxSpeed){

  Position roverPos;
  double speed;
  double dir;
  double PI = atan(1.0)*4;

  obj.getValue(&roverPos,"Position");
  obj.getValue(&speed,"Speed");
  obj.getValue(&dir,"Heading");

  string dSpeed[] ={"al","ar","a-",
		    "bl","br","b-",
		    "-l","-r","--"};  

  for(int i=0;i<9;i++){

    double cSpeed = speed;
    double cDir = dir;
    string curr = dSpeed[i];
    positions[dSpeed[i]] = roverPos;

    for(int j=0;j<time;j++){

      if(curr[0]=='a' && cSpeed + 0.5 <= maxSpeed)
	cSpeed += 0.5;

      if(curr[0]=='b' && cSpeed - 0.5 >= 0)
	cSpeed -= 0.5;

      if(curr[1] == 'l'){
	cDir += maxTurn;
	
	while(cDir >= 360)
	  cDir -= 360;
      }

      if(curr[1] == 'r'){
	cDir -= maxTurn;

	while(cDir < 0)
	  cDir += 360;
      }
	
      positions[dSpeed[i]].setX(positions[dSpeed[i]].getX() + cSpeed*cos(cDir*PI/180));
      positions[dSpeed[i]].setY(positions[dSpeed[i]].getY() + cSpeed*sin(cDir*PI/180));
    }    
  }
}

void InstructionGAPTest::setUp(){
  
}

void InstructionGAPTest::tearDown(){

}

void InstructionGAPTest::validateResults(map<string,Position> &pos,string * names,Position * dirs,int size){

  for(int i =0;i<size;i++){

    Position goodPos = pos[names[i]];
    Position testPos = dirs[i];

    //Check that the resulting position is similar enough to the
    //position that should be guessed
    CPPUNIT_ASSERT(goodPos.getX() + 0.001 >= testPos.getX() &&
    		   goodPos.getX() - 0.001 <= testPos.getX() &&
    		   goodPos.getY() + 0.001 >= testPos.getY() &&
    		   goodPos.getY() - 0.001 <= testPos.getY());
  }
}

void InstructionGAPTest::testGAP(){

  double PI = atan(1.0)*4;
  map<string,Position> allPos;
  Position res1[9];
  string res2[9];
  double time = 5;
  int ip = 0;
  
  //Check for all all degree values form 0 to 360
  for(int i=0;i<=360;i++){

    double x = rand() % 100;
    double y = rand() % 100;
    double speed = rand() % 10;
    double heading = i*PI/180;
    double maxSpeed=0;
    double maxTurn=0;
    int time = rand() % 10;
    MemoryHandler mem;    
    stringstream s;
    s << time;
    vector<string> args;
    args.push_back(string("posArray"));
    args.push_back(string("nameArray"));
    args.push_back(s.str());

    SpaceObject obj(x,y,1,speed,i*PI/180);
    ip = 0;
    int ip2 = ip;
    int argc = 3;

    mem.setValue(NULL,STRING,"nameArray:9");
    mem.setValue(NULL,POSITION,"posArray:9");
    mem.setValue(&obj,POSITION,"Position");
    mem.setValue(&heading,DOUBLE,"Heading");
    mem.setValue(&speed,DOUBLE,"Speed");
    mem.getValue(&maxSpeed,"MaxSpeed");
    mem.getValue(&maxTurn,"MaxTurn");



    Instruction_GAP gap = Instruction_GAP(&argc,args);
    
    CPPUNIT_ASSERT(gap.execute(&mem,&ip2) == 0);
    CPPUNIT_ASSERT(0 == ip);

    for(int i=0;i<9;i++){
      stringstream arg0,arg1;
      arg0 << args[0] << "[" << i << "]";
      arg1 << args[1] << "[" << i << "]";

      mem.getValue(&(res1[i]),arg0.str());
      mem.getValue(&(res2[i]),arg1.str());
    }

    this->createAllPossibilities(allPos,obj,time,maxSpeed,maxTurn);
    
    this->validateResults(allPos,res2,res1,9);
    
  }
}

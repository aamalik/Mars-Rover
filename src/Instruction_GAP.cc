/**
 * @file Instruction_GAP
 * @brief Implementation of the Instruction_GAP class
 */ 

#include <iostream>
#include <vector>
#include <string>
#include <math.h>

#include "../include/InstructionIF.hh"
#include "../include/Instruction_GAP.hh"
#include "../include/MemoryHandler.hh"
#include "Parser.hh"

using namespace std;

Instruction_GAP::Instruction_GAP(int* ret, std::vector< std::string > _args) {
	args = _args;

	*ret = 0;
}

Instruction_GAP::~Instruction_GAP() {
	args.clear();
}

int Instruction_GAP::execute(MemoryHandler* memoryLocation,int* instructionPointer) {

  Position roverPos;
  double speed;
  double dir;
  int time;
  double PI = atan(1.0)*4;
  double maxSpeed = 0;
  double maxTurn = 0;

  if(Parser::parseImmediate(&time,this->args[2]) != 0){

    cerr << "Unable to parse argument " << this->args[2] << endl;
    return 1;
  }
  
  if(time<0){

    cerr << "The Instruction GAP requires a positive time" << endl;
    return 1;
  }
  
  memoryLocation->getValue(&roverPos,"Position");
  memoryLocation->getValue(&speed,"Speed");
  memoryLocation->getValue(&dir,"Heading");
  memoryLocation->getValue(&maxSpeed,"MaxSpeed");
  memoryLocation->getValue(&maxTurn,"MaxTurn");

  string dSpeedArr[] ={"al","ar","a-",
		       "bl","br","b-",
		       "-l","-r","--"};

  vector<string> dSpeed;
  vector<Position> positions;

  for(int i=0;i<9;i++){

    double cSpeed = speed;
    double cDir = dir;
    dSpeed.push_back(dSpeedArr[i]);
    string curr = dSpeed[i];
    positions.push_back(roverPos);

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
	
      positions[i].setX(positions[i].getX() + cSpeed*cos(cDir*PI/180));
      positions[i].setY(positions[i].getY() + cSpeed*sin(cDir*PI/180));
      
    }    
  }

  for(int i=0;i<2;i++){
    if(this->args[i].find("[") != string::npos)
      this->args[i] = this->args[i].substr(0,this->args[i].find("["));
  
    else if(this->args[i].find(":") != string::npos)
      this->args[i] = this->args[i].substr(0,this->args[i].find(":"));
  }
  
  for(unsigned int i=0;i<positions.size();i++){

    stringstream arg0,arg1;
    arg0 << this->args[0] << "[" << i <<"]";
    arg1 << this->args[1] << "[" << i <<"]";

    Position p = positions[i];
    string s = dSpeed[i];

    if(memoryLocation->setValue(&p,POSITION,arg0.str()) != 0 ||
       memoryLocation->setValue(&s,STRING,arg1.str()) != 0){

      cerr << "Unable to set the value of " << this->args[0];
      cerr << " and " << this->args[1] << endl;
      return 1;
    }
  }

  return 0;
}

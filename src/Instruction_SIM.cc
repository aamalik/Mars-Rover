/**
 * @file Instruction_SIM
 * @brief Implementation of the Instruction_SIM class
  */ 

#include <vector>
#include <string>
#include <math.h>
#include <iostream>
#include <stdlib.h>

#include "Parser.hh"
#include "../include/InstructionIF.hh"
#include "../include/Instruction_SIM.hh"
#include "../include/MemoryHandler.hh"

using namespace std;

Instruction_SIM::Instruction_SIM(int* ret, std::vector< std::string > _args) {
	args = _args;

	*ret = 0;
}

Instruction_SIM::~Instruction_SIM() {
	args.clear();
}

int Instruction_SIM::execute(MemoryHandler* memoryLocation,int* instructionPointer) {

  SpaceObject obj(0,0,0,0,0);

  if(memoryLocation->getValue(&obj,this->args[2]) != 0){

    cerr << "The object " << args[2] << " was not found.";
    return 1;
  }

  Position p;
  double dir;
  double speed;
  int time;

  if(Parser::parseImmediate(&time,this->args[1]) != 0){

    cerr << "Failed to convet " << this->args[1] << " to a number.";
  }

  obj.getValue(&p,"Position");
  obj.getValue(&dir,"Heading");
  obj.getValue(&speed,"Speed");
  

  p.setX(p.getX() + cos(dir) * speed * time);
  p.setY(p.getY() + sin(dir) * speed * time);

  return memoryLocation->setValue(&p,POSITION,this->args[0]);
}

/**
 * @file Instruction_DST
 * @brief Implementation of the Instruction_DST class
 */ 

#include <vector>
#include <string>
#include <iostream>
#include <math.h>

#include "../include/InstructionIF.hh"
#include "../include/Instruction_DST.hh"
#include "../include/MemoryHandler.hh"


using namespace std;

Instruction_DST::Instruction_DST(int* ret, std::vector< std::string > _args) {
	args = _args;

	*ret = 0;
}

Instruction_DST::~Instruction_DST() {
	args.clear();
}

int Instruction_DST::execute(MemoryHandler* memoryLocation,int* instructionPointer) {

  
  SpaceObject obj1(0,0,0,0,0), obj2(0,0,0,0,0);

  if(memoryLocation->getValue(&obj1,this->args[1]) != 0 ||
     memoryLocation->getValue(&obj2,this->args[2]) != 0){

    cerr << "The value " << this->args[0] << " or ";
    cerr << this->args[1] << " is not defined."<<endl;
    return 1;
  }
  
  Position p1,p2;
  obj1.getValue(&p1,"Position");
  obj2.getValue(&p2,"Position");

  double dist = sqrt(pow((p1.getX() - p2.getX()),2)
		     + pow((p1.getY() - p2.getY()),2));

  return memoryLocation->setValue(&dist,DOUBLE,this->args[0]);
}

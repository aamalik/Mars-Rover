/**
 * @file Instruction_GTA
 * @brief Implementation of the Instruction_GTA class
 */ 

#include <vector>
#include <string>
#include <math.h>

#include "../include/InstructionIF.hh"
#include "../include/Instruction_GTA.hh"
#include "../include/MemoryHandler.hh"
#include "../include/Helper.hh"

#define PI 3.14159265

using namespace std;

Instruction_GTA::Instruction_GTA(int* ret, std::vector< std::string > _args) {
	args = _args;

	*ret = 0;
}

Instruction_GTA::~Instruction_GTA() {
	args.clear();
}

int Instruction_GTA::execute(MemoryHandler* memoryLocation,int* instructionPointer) {

  Position p;

  if(memoryLocation->getValue(&p,this->args[1]) != 0){

    cerr << "The variable " << this->args[1] << " has not been defined.";
    return 1;
  }

  double angle = 0;

  angle = atan2( p.getY(), p.getX() ) * 180 / PI;

  return memoryLocation->setValue(&angle,DOUBLE,this->args[0]);
}

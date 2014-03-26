/**
 * @file Instruction_wat
 * @brief Implementation of the Instruction_wat class
 */ 

#include <vector>
#include <string>

#include "../include/InstructionIF.hh"
#include "../include/Instruction_wat.hh"
#include "../include/MemoryHandler.hh"
#include "../include/ArgumentType.hh"
#include "../include/Helper.hh"

using namespace std;

#define FAIL_ON(x) if(x){ return IMEMERROR; } 
static const char filename[] = "Instruction_wat";

Instruction_wat::Instruction_wat(int* ret, std::vector< std::string > _args) {
	args = _args;

	if (args.size() != 0) {
		*ret = 1;
		return ;
	}

	*ret = 0;
}

Instruction_wat::~Instruction_wat() {
	args.clear();
}

int Instruction_wat::execute(MemoryHandler* memoryLocation,int* instructionPointer) {
	// Sanity check
	if (memoryLocation == NULL || instructionPointer == NULL)
		FAIL_ON(true);

	return IWAIT;
}
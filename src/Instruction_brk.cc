/**
 * @file Instruction_brk
 * @brief Implementation of the Instruction_brk class
 */ 

#include <vector>
#include <string>

#include "../include/InstructionIF.hh"
#include "../include/Instruction_brk.hh"
#include "../include/MemoryHandler.hh"
#include "../include/ArgumentType.hh"
#include "../include/Helper.hh"

using namespace std;

#define FAIL_ON(x) if(x){ return IMEMERROR; } 
static const char filename[] = "Instruction_brk";

Instruction_brk::Instruction_brk(int* ret, std::vector< std::string > _args) {
	args = _args;

	if (args.size() != 0) {
		*ret = 1;
		return ;
	}

	*ret = 0;
}

Instruction_brk::~Instruction_brk() {
	args.clear();
}

int Instruction_brk::execute(MemoryHandler* memoryLocation,int* instructionPointer) {
	// Sanity check
	if (memoryLocation == NULL || instructionPointer == NULL)
		FAIL_ON(true);

	return ICONTINUE;
}
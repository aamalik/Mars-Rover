/**
 * @file Instruction_cln
 * @brief Implementation of the Instruction_cln class
 */ 

#include <vector>
#include <string>

#include "../include/InstructionIF.hh"
#include "../include/Instruction_cln.hh"
#include "../include/MemoryHandler.hh"
#include "../include/ArgumentType.hh"
#include "../include/Helper.hh"

using namespace std;

#define FAIL_ON(x) if(x){ return IMEMERROR; } 
static const char filename[] = "Instruction_cln";

Instruction_cln::Instruction_cln(int* ret, std::vector< std::string > _args) {
	args = _args;

	if (args.size() != 0) {
		*ret = 1;
		return ;
	}

	*ret = 0;
}

Instruction_cln::~Instruction_cln() {
	args.clear();
}

int Instruction_cln::execute(MemoryHandler* memoryLocation,int* instructionPointer) {
	// Sanity check
	if (memoryLocation == NULL || instructionPointer == NULL)
		FAIL_ON(true);

	_deep_debug_("%s Do the operation\n",filename);
	int ret = memoryLocation->cleanDynamicData();
	FAIL_ON (ret);

	return ICONTINUE;
}
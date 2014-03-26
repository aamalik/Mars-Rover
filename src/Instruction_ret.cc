/**
 * @file Instruction_ret
 * @brief Implementation of the Instruction_ret class
 */ 

#include <vector>
#include <string>

#include "../include/InstructionIF.hh"
#include "../include/Instruction_ret.hh"
#include "../include/MemoryHandler.hh"
#include "../include/ArgumentType.hh"
#include "../include/Helper.hh"

using namespace std;

#define FAIL_ON(x) if(x){ return IMEMERROR; } 
static const char filename[] = "Instruction_ret";

Instruction_ret::Instruction_ret(int* ret, std::vector< std::string > _args) {
	args = _args;

	if (args.size() != 1) {
		*ret = 1;
		return ;
	}

	*ret = 0;
}

Instruction_ret::~Instruction_ret() {
	args.clear();
}

int Instruction_ret::execute(MemoryHandler* memoryLocation,int* instructionPointer) {
	// Sanity check
	if (memoryLocation == NULL || instructionPointer == NULL)
		FAIL_ON(true);

	ArgumentType t1;
	t1 = NOTYPE;
	int ret;
	string v1;

	_deep_debug_("%s get types of args\n",filename);
	ret = memoryLocation->getType(&t1,args[0]);
	FAIL_ON(ret != 0);

	FAIL_ON(t1 != STRING);

	_deep_debug_("%s Get Values\n",filename);
	ret = memoryLocation->getValue((void*)&v1,args[0]);
	FAIL_ON(ret != 0);

	_deep_debug_("%s Do the operation\n",filename);
	memoryLocation->setReturnString(v1 + ";");

	return IRETURN;
}
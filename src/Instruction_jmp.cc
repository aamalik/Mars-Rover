/**
 * @file Instruction_jmp
 * @brief Implementation of the Instruction_jmp class
 */ 

#include <vector>
#include <string>

#include "../include/InstructionIF.hh"
#include "../include/Instruction_jmp.hh"
#include "../include/MemoryHandler.hh"
#include "../include/ArgumentType.hh"
#include "../include/Helper.hh"
#include "../include/Parser.hh"

using namespace std;

#define FAIL_ON(x) if(x){ return IMEMERROR; } 
static const char filename[] = "Instruction_jmp";

Instruction_jmp::Instruction_jmp(int* ret, std::vector< std::string > _args) {
	args = _args;

	if (args.size() != 1) {
		*ret = 1;
		return ;
	}

	int i;
	ArgumentType t = NOTYPE;
	if (Parser::parseGetTypeImmediate(&t,args[0]) != 0) 
		goto fail;
	if (t != INT) 
		goto fail;
	if (Parser::parseImmediate(&i,args[0]) != 0) 
		goto fail;
	if (i < 0) 
		goto fail;

	*ret = 0;
	return ;

fail:
	*ret = 1;
	return ;
}

Instruction_jmp::~Instruction_jmp() {
	args.clear();
}

int Instruction_jmp::execute(MemoryHandler* memoryLocation,int* instructionPointer) {

	// Sanity check
	if (memoryLocation == NULL || instructionPointer == NULL)
		FAIL_ON(true);

	ArgumentType t1;
	int instrPointer;
	int ret;

	_deep_debug_("%s get types of args\n",filename);
	ret = memoryLocation->getType(&t1,args[0]);
	FAIL_ON(ret != 0);

	FAIL_ON(t1 != INT);

	_deep_debug_("%s Get Values\n",filename);
	ret = memoryLocation->getValue(&instrPointer,args[0]);
	FAIL_ON(ret != 0);

	_deep_debug_("%s Do the operation\n",filename);
	*instructionPointer = instrPointer;
 	
	return 0;
}
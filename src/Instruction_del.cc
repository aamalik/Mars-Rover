/**
 * @file Instruction_del
 * @brief Implementation of the Instruction_del class
 */ 

#include <vector>
#include <string>

#include "../include/InstructionIF.hh"
#include "../include/Instruction_del.hh"
#include "../include/MemoryHandler.hh"
#include "../include/ArgumentType.hh"
#include "../include/Helper.hh"

using namespace std;

#define FAIL_ON(x) if(x){ return IMEMERROR; } 
static const char filename[] = "Instruction_del";

Instruction_del::Instruction_del(int* ret, std::vector< std::string > _args) {
	args = _args;

	if (args.size() != 1) {
		*ret = 1;
		return ;
	}

	string s;
	ArgumentType t = NOTYPE;
	if (Parser::parseGetTypeImmediate(&t,args[0]) != 0) 
		goto fail;
	if (t != STRING) 
		goto fail;
	if (Parser::parseImmediate(&s,args[0]) != 0) 
		goto fail;

	*ret = 0;
	return ;

fail:
	*ret = 1;
	return ;
}

Instruction_del::~Instruction_del() {
	args.clear();
}

int Instruction_del::execute(MemoryHandler* memoryLocation,int* instructionPointer) {

	// Sanity check
	if (memoryLocation == NULL || instructionPointer == NULL)
		FAIL_ON(true);

	ArgumentType t1;
	t1 = NOTYPE;
	int ret;
	string s;

	if (Parser::parseImmediate(&s,args[0]) != 0) 
		FAIL_ON(true);

	_deep_debug_("%s get types of args\n",filename);
	ret = memoryLocation->getType(&t1,s);
	FAIL_ON(ret != 0);

	FAIL_ON (t1 != INT &&
			 t1 !=  DOUBLE &&
			 t1 !=  POSITION &&
			 t1 !=  STRING &&
			 t1 !=  INTARRAY &&
			 t1 !=  DOUBLEARRAY &&
			 t1 !=  POSITIONARRAY &&
			 t1 !=  STRINGARRAY);

	_deep_debug_("%s Delete Value\n",filename);
	ret = memoryLocation->deleteValue(s);
	FAIL_ON(ret != 0);

	return 0;
}
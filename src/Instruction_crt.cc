/**
 * @file Instruction_crt
 * @brief Implementation of the Instruction_crt class
 */ 

#include <vector>
#include <string>

#include "../include/InstructionIF.hh"
#include "../include/Instruction_crt.hh"
#include "../include/MemoryHandler.hh"
#include "../include/ArgumentType.hh"
#include "../include/Helper.hh"

using namespace std;

#define FAIL_ON(x) if(x){ return IMEMERROR; } 
static const char filename[] = "Instruction_crt";

Instruction_crt::Instruction_crt(int* ret, std::vector< std::string > _args) {
	args = _args;

	if (args.size() != 2) {
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
	if (s != "Int" && 
		s != "Double" && 
		s != "Position" && 
		s != "String") 
		goto fail;
	if (Parser::parseGetTypeImmediate(&t,args[1]) != 0) 
		goto fail;
	if (t != STRING) 
		goto fail;
	if (Parser::parseImmediate(&s,args[1]) != 0) 
		goto fail;

	*ret = 0;
	return ;

fail:
	*ret = 1;
	return ;
}

Instruction_crt::~Instruction_crt() {
	args.clear();
}

int Instruction_crt::execute(MemoryHandler* memoryLocation,int* instructionPointer) {

	// Sanity check
	if (memoryLocation == NULL || instructionPointer == NULL)
		FAIL_ON(true);

	ArgumentType t1,t2;
	t1 = t2 = NOTYPE;
	int ret;
	string v1;
	string v2;
	int int_init = 0;
	double double_init = 0.0;
	Position position_init;
	string string_init = "";

	_deep_debug_("%s get types of args\n",filename);
	ret = memoryLocation->getType(&t1,args[0]);
	FAIL_ON(ret != 0);
	ret = memoryLocation->getType(&t2,args[1]);
	FAIL_ON(ret != 0);

	FAIL_ON(t1 != STRING);
	FAIL_ON(t2 != STRING);

	_deep_debug_("%s Get Values\n",filename);
	ret = memoryLocation->getValue((void*)&v1,args[0]);
	FAIL_ON(ret != 0);
	ret = memoryLocation->getValue((void*)&v2,args[1]);
	FAIL_ON(ret != 0);

	_deep_debug_("%s Do the operation\n",filename);
	if (v1 == "Int") {
		ret = memoryLocation->setValue((void*)&int_init,INT,v2);
		FAIL_ON(ret != 0);
	} else if (v1 == "Double") {
		ret = memoryLocation->setValue((void*)&double_init,DOUBLE,v2);
		FAIL_ON(ret != 0);
	} else if (v1 == "Position") {
		ret = memoryLocation->setValue((void*)&position_init,POSITION,v2);
		FAIL_ON(ret != 0);
	} else if (v1 == "String") {
		ret = memoryLocation->setValue((void*)&string_init,STRING,v2);
		FAIL_ON(ret != 0);
	} else {
		FAIL_ON(true);
	}

	return 0;
}
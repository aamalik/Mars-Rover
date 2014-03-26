/**POSI
 * @file Instruction_cra
 * @brief Implementation of the Instruction_cra class
 */ 

#include <vector>
#include <string>
#include <iostream>

#include "../include/InstructionIF.hh"
#include "../include/Instruction_cra.hh"
#include "../include/MemoryHandler.hh"
#include "../include/ArgumentType.hh"
#include "../include/Helper.hh"
#include "../include/Parser.hh"

using namespace std;

#define FAIL_ON(x) if(x){ return IMEMERROR; } 
static const char filename[] = "Instruction_cra";

Instruction_cra::Instruction_cra(int* ret, std::vector< std::string > _args) {
	args = _args;

	if (args.size() != 3) {
		*ret = 1;
		return ;
	}

	string s;
	ArgumentType t = NOTYPE;
	int i;
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
	if (t != INT) 
		goto fail;
	if (Parser::parseImmediate(&i,args[1]) != 0) 
		goto fail;
	if (i < 0 || i > ARRAYMAXSIZE) 
		goto fail;
	if (Parser::parseGetTypeImmediate(&t,args[2]) != 0) 
		goto fail;
	if (t != STRING) 
		goto fail;
	if (Parser::parseImmediate(&s,args[2]) != 0) 
		goto fail;

	*ret = 0;
	return ;

fail:
	*ret = 1;
	return ;
}

Instruction_cra::~Instruction_cra() {
	args.clear();
}

int Instruction_cra::execute(MemoryHandler* memoryLocation,int* instructionPointer) {
	// Sanity check
	if (memoryLocation == NULL || instructionPointer == NULL)
		FAIL_ON(true);

	ArgumentType t1,t2,t3;
	t1 = t2 = t3 = NOTYPE;
	int ret;
	string v1;
	int v2;
	string v3;
	string comp,conv;

	_deep_debug_("%s get types of args\n",filename);
	ret = memoryLocation->getType(&t1,args[0]);
	FAIL_ON(ret != 0);
	ret = memoryLocation->getType(&t2,args[1]);
	FAIL_ON(ret != 0);
	ret = memoryLocation->getType(&t3,args[2]);
	FAIL_ON(ret != 0);

	FAIL_ON(t1 != STRING);
	FAIL_ON(t2 != INT);
	FAIL_ON(t3 != STRING);

	_deep_debug_("%s Get Values\n",filename);
	ret = memoryLocation->getValue((void*)&v1,args[0]);
	FAIL_ON(ret != 0);
	ret = memoryLocation->getValue((void*)&v2,args[1]);
	FAIL_ON(ret != 0);
	ret = memoryLocation->getValue((void*)&v3,args[2]);
	FAIL_ON(ret != 0);

	if (v2 < 0 || v2 > ARRAYMAXSIZE)
		return 1;

	stringstream ss;
	ss << v2;
	conv = ss.str();
	comp = v3 + ":" + conv;


	_deep_debug_("%s Do the operation\n",filename);
	if (v1 == "Int") {
		ret = memoryLocation->setValue(NULL,INT,comp);
		FAIL_ON(ret != 0);
	} else if (v1 == "Double") {
		ret = memoryLocation->setValue(NULL,DOUBLE,comp);
		FAIL_ON(ret != 0);
	} else if (v1 == "Position") {
		ret = memoryLocation->setValue(NULL,POSITION,comp);
		FAIL_ON(ret != 0);
	} else if (v1 == "String") {
		ret = memoryLocation->setValue(NULL,STRING,comp);
		FAIL_ON(ret != 0);
	} else {
		FAIL_ON(true);
	}

	return 0;
}
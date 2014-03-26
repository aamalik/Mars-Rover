/**
 * @file Instruction_iee
 * @brief Implementation of the Instruction_iee class
 */ 

#include <vector>
#include <string>

#include "../include/InstructionIF.hh"
#include "../include/Instruction_iee.hh"
#include "../include/MemoryHandler.hh"
#include "../include/ArgumentType.hh"
#include "../include/Helper.hh"
#include "../include/Parser.hh"

using namespace std;

#define FAIL_ON(x) if(x){ return IMEMERROR; } 
static const char filename[] = "Instruction_iee";

Instruction_iee::Instruction_iee(int* ret, std::vector< std::string > _args) {
	args = _args;

	if (args.size() != 4) {
		*ret = 1;
		return ;
	}

	int i;
	ArgumentType t = NOTYPE;
	if (Parser::parseGetTypeImmediate(&t,args[2]) != 0) 
		goto fail;
	if (t != INT) 
		goto fail;
	if (Parser::parseImmediate(&i,args[2]) != 0) 
		goto fail;
	if (i < 0) 
		goto fail;
	if (Parser::parseGetTypeImmediate(&t,args[3]) != 0) 
		goto fail;
	if (t != INT) 
		goto fail;
	if (Parser::parseImmediate(&i,args[3]) != 0) 
		goto fail;
	if (i < 0) 
		goto fail;

	*ret = 0;
	return ;

fail:
	*ret = 1;
	return ;
}

Instruction_iee::~Instruction_iee() {
	args.clear();
}

int Instruction_iee::execute(MemoryHandler* memoryLocation,int* instructionPointer) {
	// Sanity check
	if (memoryLocation == NULL || instructionPointer == NULL)
		FAIL_ON(true);

	ArgumentType t1,t2,t3,t4;
	t1 = t2 = t3 = t4 = NOTYPE;
	int ret;
	int i1,i2;
	double d1,d2;

	_deep_debug_("%s get types of args\n",filename);
	ret = memoryLocation->getType(&t1,args[0]);
	FAIL_ON(ret != 0);
	ret = memoryLocation->getType(&t2,args[1]);
	FAIL_ON(ret != 0);
	ret = memoryLocation->getType(&t3,args[2]);
	FAIL_ON(ret != 0);
	ret = memoryLocation->getType(&t4,args[3]);
	FAIL_ON(ret != 0);

	FAIL_ON(t1 != t2);
	FAIL_ON(t3 != INT);
	FAIL_ON(t4 != INT);

	void *v1,*v2,*v3,*v4;

	_deep_debug_("%s Create variables\n",filename);
	switch(t1) {
		case INT:
			v1 = new int;
			v2 = new int;
			v3 = new int;
			v4 = new int;
			break;
		case DOUBLE:
			v1 = new double;
			v2 = new double;
			v3 = new int;
			v4 = new int;
			break;
		default: 
			FAIL_ON(true);
	}

	_deep_debug_("%s Get Values\n",filename);
	ret = memoryLocation->getValue(v1,args[0]);
	FAIL_ON(ret != 0);
	ret = memoryLocation->getValue(v2,args[1]);
	FAIL_ON(ret != 0);
	ret = memoryLocation->getValue(v3,args[2]);
	FAIL_ON(ret != 0);
	ret = memoryLocation->getValue(v4,args[3]);
	FAIL_ON(ret != 0);

	_deep_debug_("%s Do the operation\n",filename);
	switch (t1) {
		case INT:
			i1 = (*((int*)v1));
			i2 = (*((int*)v2));
			if (i1 == i2) 
				*instructionPointer = (*((int*)v3));
			else 
				*instructionPointer = (*((int*)v4));
			break;
		case DOUBLE:
			d1 = (*((double*)v1));
			d2 = (*((double*)v2));
			// get the abs difference
			if (d1-d2 < DOUBLEPRECISION && d2-d1 < DOUBLEPRECISION) 
				*instructionPointer = (*((int*)v3));
			else 
				*instructionPointer = (*((int*)v4));
			break;
		default: 
			FAIL_ON(true);
	}

	_deep_debug_("%s Delete Values\n",filename);
	switch(t1) {
		case INT:
			delete ((int*)v1);
			delete ((int*)v2);
			delete ((int*)v3);
			delete ((int*)v4);
			break;
		case DOUBLE:
			delete ((double*)v1);
			delete ((double*)v2);
			delete ((int*)v3);
			delete ((int*)v4);
			break;
		default: 
			FAIL_ON(true);
	}
	return 0;
}
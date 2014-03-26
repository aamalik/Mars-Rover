/**
 * @file Instruction_put
 * @brief Implementation of the Instruction_put class

 */ 

#include <vector>
#include <string>

#include "../include/InstructionIF.hh"
#include "../include/Instruction_put.hh"
#include "../include/MemoryHandler.hh"
#include "../include/ArgumentType.hh"
#include "../include/Helper.hh"

using namespace std;

#define FAIL_ON(x) if(x){ return IMEMERROR; } 
static const char filename[] = "Instruction_put";

Instruction_put::Instruction_put(int* ret, std::vector< std::string > _args) {
	args = _args;

	if (args.size() != 2) {
		*ret = 1;
		return ;
	}

	*ret = 0;
}

Instruction_put::~Instruction_put() {
	args.clear();
}

int Instruction_put::execute(MemoryHandler* memoryLocation,int* instructionPointer) {

	// Sanity check
	if (memoryLocation == NULL || instructionPointer == NULL)
		FAIL_ON(true);

	ArgumentType t1,t2;
	t1 = t2 = NOTYPE;
	int ret;

	_deep_debug_("%s get types of args\n",filename);
	ret = memoryLocation->getType(&t1,args[0]);
	FAIL_ON(ret != 0);
	ret = memoryLocation->getType(&t2,args[1]);
	FAIL_ON(ret != 0);

	FAIL_ON(t1 != t2);

	void *v2;

	_deep_debug_("%s Create variables\n",filename);
	switch(t1) {
		case INT:
			v2 = new int;
			break;
		case DOUBLE:
			v2 = new double;
			break;
		case POSITION:
			v2 = new Position;
			break;
		case STRING:
			v2 = new string;
			break;
		default: 
			FAIL_ON(true);
	}

	_deep_debug_("%s Get Values\n",filename);
	ret = memoryLocation->getValue(v2,args[1]);
	FAIL_ON(ret != 0);

	_deep_debug_("%s Do the operation\n",filename);
	ret = memoryLocation->setValue(v2,t1,args[0]);

	_deep_debug_("%s Delete Values\n",filename);
	switch(t1) {
		case INT:
			delete ((int*)v2);
			break;
		case DOUBLE:
			delete ((double*)v2);
			break;
		case POSITION:
			delete ((Position*)v2);
			break;
		case STRING:
			delete ((string*)v2);
			break;
		default: 
			FAIL_ON(true);
	}
	return 0;
}
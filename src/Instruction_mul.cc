/**
 * @file Instruction_mul
 * @brief Implementation of the Instruction_mul class
 */ 

#include <vector>
#include <string>

#include "../include/InstructionIF.hh"
#include "../include/Instruction_mul.hh"
#include "../include/MemoryHandler.hh"
#include "../include/ArgumentType.hh"
#include "../include/Helper.hh"

using namespace std;

#define FAIL_ON(x) if(x){ return IMEMERROR; } 
static const char filename[] = "Instruction_mul";

Instruction_mul::Instruction_mul(int* ret, std::vector< std::string > _args) {
	args = _args;

	if (args.size() != 3) {
		*ret = 1;
		return ;
	}

	*ret = 0;
}

Instruction_mul::~Instruction_mul() {
	args.clear();
}

int Instruction_mul::execute(MemoryHandler* memoryLocation,int* instructionPointer) {
	
	if (memoryLocation == NULL || instructionPointer == NULL)
		FAIL_ON(true);

	ArgumentType t1,t2,t3;
	t1 = t2 = t3 = NOTYPE;
	int ret;

	_deep_debug_("%s get types of args\n",filename);
	ret = memoryLocation->getType(&t1,args[0]);
	FAIL_ON(ret != 0);
	ret = memoryLocation->getType(&t2,args[1]);
	FAIL_ON(ret != 0);
	ret = memoryLocation->getType(&t3,args[2]);
	FAIL_ON(ret != 0);

	FAIL_ON(t1 != t2);
	FAIL_ON( t2 == INT && t3 != INT );
	FAIL_ON( t2 == DOUBLE && t3 != DOUBLE );
	FAIL_ON( t2 == POSITION && t3 != DOUBLE );

	void *v1,*v2,*v3;

	_deep_debug_("%s Create variables\n",filename);
	switch(t1) {
		case INT:
			v1 = new int;
			v2 = new int;
			v3 = new int;
			break;
		case DOUBLE:
			v1 = new double;
			v2 = new double;
			v3 = new double;
			break;
		case POSITION:
			v1 = new Position;
			v2 = new Position;
			v3 = new double;
			break;
		default: 
			FAIL_ON(true);
	}

	_deep_debug_("%s Get Values\n",filename);
	ret = memoryLocation->getValue(v2,args[1]);
	FAIL_ON(ret != 0);
	ret = memoryLocation->getValue(v3,args[2]);
	FAIL_ON(ret != 0);

	_deep_debug_("%s Do the operation\n",filename);
	switch (t1) {
		case INT:	
			*((int*)v1) = (*((int*)v2)) * (*((int*)v3));
			break;
		case DOUBLE:	
			*((double*)v1) = (*((double*)v2)) * (*((double*)v3));
			break;
		case POSITION:
			((Position*)v1)->setX( 
				((Position*)v2)->getX() * (*((double*)v3)));
			((Position*)v1)->setY( 
				((Position*)v2)->getY() * (*((double*)v3)));
			break;
		default: 
			FAIL_ON(true);
	}

	_deep_debug_("%s Set Value\n",filename);
	ret = memoryLocation->setValue(v1,t1,args[0]);
	FAIL_ON(ret != 0);

	_deep_debug_("%s Delete Values\n",filename);
	switch(t1) {
		case INT:
			delete ((int*)v1);
			delete ((int*)v2);
			delete ((int*)v3);
			break;
		case DOUBLE:
			delete ((double*)v1);
			delete ((double*)v2);
			delete ((double*)v3);
			break;
		case POSITION:
			delete ((Position*)v1);
			delete ((Position*)v2);
			delete ((double*)v3);
			break;
		default: 
			FAIL_ON(true);
	}
	return 0;
}
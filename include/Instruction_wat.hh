/**
 * Instruction wat header class
 */

#ifndef _INSTRUCTION_WAT_HH
#define _INSTRUCTION_WAT_HH

#include <vector>
#include <string>

#include "InstructionIF.hh"

class Instruction_wat : public InstructionIF {
private:
	int argc;
	std::vector< std::string > args;
public:
    // Constructors and destructors
	/**
     * @brief Public constructor of Instruction_wat class
     * @param  ret   Address in memory to write return value to.
     * @param  args  Vector of arguments needed for instruction.
     */
	Instruction_wat(int* ret, std::vector< std::string > _args);
	~Instruction_wat();

	/**
	* @brief Method to execute the wat instruction of the Brain File
	* @param  memoryLocation    Pointer to MemoryHandler for memory management.
    * @param  instrPointer      Pointer to desired instruction.
    * @return If successful, 0, 1 otherwise.
	 */
	int execute(MemoryHandler* memoryLocation,int* instructionPointer);
};

 #endif
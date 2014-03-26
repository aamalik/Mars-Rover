/**
 * Instruction GAP header class
 */

#ifndef _INSTRUCTION_GAP_HH
#define _INSTRUCTION_GAP_HH

#include <vector>
#include <string>

#include "InstructionIF.hh"

/**
 * @class This instruction calculates all the possible locations towards which the
 * rover can after the specified ammount of time.
 */
class Instruction_GAP : public InstructionIF {
private:
	int argc;
	std::vector< std::string > args;
public:
    // Constructors and destructors
	/**
     * @brief Public constructor of Instruction_GAP class
     * @param  ret   Address in memory to write return value to.
     * @param  args  Vector of arguments needed for instruction.
     */
	Instruction_GAP(int* ret, std::vector< std::string > _args);
	~Instruction_GAP();

	/**
	* @brief Method to execute the GAP instruction of the Brain File
	* @param  memoryLocation    Pointer to MemoryHandler for memory management.
    * @param  instrPointer      Pointer to desired instruction.
    * @return If successful, 0, 1 otherwise.
	 */
	int execute(MemoryHandler* memoryLocation,int* instructionPointer);
};

 #endif

#ifndef _INSTRUCTIONIF_HH
#define _INSTRUCTIONIF_HH

/****************************************************************************/
/* Includes                                                                 */
/****************************************************************************/
#include <string>
#include <vector>
#include "../include/MemoryHandler.hh"

class MemoryHandler;

#define DOUBLEPRECISION 0.0000000001
#define ARRAYMAXSIZE 1025

enum Status {
	ICONTINUE, 
	IRETURN, 
	IMEMERROR, 
	IWAIT
};


/****************************************************************************/
/* Prototypes                                                               */
/****************************************************************************/

/**
 * @class InstructionIF
 * Interface InstructionIF represent one command of Brain file and is responsible
 * for executing them and returning results.
 */
class InstructionIF {
    
private:
    // Private members
	int argc; /**< Number of passed arguments. */
	std::vector <std::string> args; /**< Vector, containing arguments. */

public:
    // Constructors and destructors
	/**
     * @brief Public constructor of InstructionIF class
     * @param  ret   Address in memory to write return value to.
     * @param  args  Vector of arguments needed for instruction.
     */
//	InstructionIF(int* ret, std::vector< std::string > _args);

     virtual ~InstructionIF() {}
    
    // Public methods
	/**
	* @brief Method to execute specific instruction of the Brain file. 
	* @param  memoryLocation    Pointer to MemoryHandler for memory management.
    * @param  instrPointer      Pointer to desired instruction.
    * @return If successful, 0, 1 otherwise.
	*/
	virtual int execute(MemoryHandler* memoryLocation, int* instrPointer) = 0;
};


#endif // ! _INSTRUCTIONIF_HH

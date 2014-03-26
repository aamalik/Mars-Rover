#ifndef _MEMORY_HANDLER_HH
#define _MEMORY_HANDLER_HH

/****************************************************************************/
/* Includes                                                                 */
/****************************************************************************/
#include <cstring>
#include <iostream>
#include <sstream>
#include <map>
#include <ctype.h>
#include <cstdlib>
#include "ArgumentType.hh"
#include "Logger.hh"
#include "SpaceObjectRegister.hh"
#include "VariableRegister.hh"
#include "RoverDataRegister.hh"
#include "MapRegister.hh"
#include "Parser.hh"

class Logger;
class SpaceObjectRegister;
class VariableRegister;
class RoverDataRegister;
class MapRegister;

using namespace std;

/****************************************************************************/
/* Prototypes                                                               */
/****************************************************************************/

/**
 * @class MemoryHandler
 * Class MemoryHandler keeps track of registers and current time, passed by map.
 * It acts like a connecting chain between Register classes and the Brain class.
 */

class MemoryHandler {

private:
    // Private members
	int ctime;  /**< Current time. */
	VariableRegister variables;  /**< VariableRegister variables. */
	SpaceObjectRegister* spaceObjects;  /**< Register to hold SpaceObjects. */
	RoverDataRegister rover;    /**< Rover details. */
	MapRegister map;    /**< Map details. */

    std::string returnString;
 
public:
    // Constructors and destructors
    
	/**
	* @brief Public constructor of the MemoryHandler class
	*/
	MemoryHandler();
    
    /**
     * @brief Public destructor of the MemoryHandler class
     */
    ~MemoryHandler();

    // Public methods
    
    /**
     * @brief Parse initial data and send it to respective registers.
     * @param   message  String to be parsed.
     * @return  If successful, 1, 0 otherwise.
     */
	int init(std::string message);

    /**
     * @brief Parse general temetry data and send it to respective registers.
     * @param   message  String to be parsed.
     * @return  If successful, 1, 0 otherwise.
     */
	int parseData(std::string message);

    /**
     * @brief Clean all data stored in the registers.
     * @return  If successful 0, 1 otherwise.
     */
	int clean();

    /**
     * @brief Clean data stored by Brain Programmer
     * @return  If successful 0, 1 otherwise.
     */
     int cleanDynamicData();
    
    /**
    * @brief Get type of the variable "name" stored in the registers.
    * @param   type  Type of the desired variable.
    * @param   name  Variable name.
    * @return  If successful, 0, error code otherwise.
    */
	int getType(ArgumentType* type, std::string name);
    
    /**
     * @brief Get value of the variable name stored in the respective register.
     * @param   value  Value that we want to set.
     * @param   name  Name of the variable to be set.
     * @return  If successful, 1, 0 otherwise.
     */
	int getValue(void* value, std::string name);
    
    /**
     * @brief Set value of the variable "name" to "value" if it's type is "type".
     * @param   value  Value, that we would like to set.
     * @param   type  Type of variable.
     * @param   name  Name of the variable that needs to be set.
     * @return  If successful, 0, error code otherwise.
     */
	int setValue(void* value, ArgumentType type, std::string name);

    /**
     * @brief Deletes the variable "name" from the respective register.
     * @param   name  Name of the variable to be cleared.
     * @return  If successful, 0, error code otherwise.
     */
    int deleteValue (std::string name);

    /**
     * @brief Setter for the returnString
     * @param aReturnString the string to be set
     */
     void setReturnString(std::string aReturnString) ;

     /**
      * @brief Getter for the returnString
      * @return the value of the returnString
      */ 
     std::string getReturnString();
};

#endif // ! _MEMORY_HANDLER_HH

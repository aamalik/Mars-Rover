#ifndef FILE_VariableRegister_SEEN
#define FILE_VariableRegister_SEEN

/****************************************************************************/
/* Includes                                                                 */
/****************************************************************************/
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include "Position.hh"
#include "ArgumentType.hh"

using namespace std;

/****************************************************************************/
/* Prototypes                                                               */
/****************************************************************************/

/**
 * @class VariableRegister
 * Class VariableRegister holds and allows to access variables, that will be
 * used while executing brain instructions (serves as a general register).
 */

class VariableRegister {

private:
    // Private members
    map<string,int> intMap; /**< Container for int variables */
    map<string,double> doubleMap;   /**< Container for double variables */
    map<string,string> stringMap;   /**< Container for string variables */
    map<string,Position> positionMap;   /**< Container for position variables */
    map<string,vector<int> > intArrayMap;   /**< Container for int vector variables */
    map<string,vector<double> > doubleArrayMap; /**< Container for double vector variables */
    map<string,vector<string> > stringArrayMap; /**< Container for string vector variables */
    map<string, vector<Position> > positionArrayMap;    /**< Container for position vector variables */
    
public:
    // Constructors and destructors
    /**
     * @brief Public constructor of the MemoryHandler class.
     */
    VariableRegister();
    
    //Public methods
    /**
     * @brief Clean all data stored in the register.
     * @return  If successful, 0, error code otherwise.
     */
    int clean();
    
    /**
     * @brief Get type of the variable "name" stored here.
     * @param   type  Type of the desired variable.
     * @param   name  Variable name.
     * @return  If successful, 0, error code otherwise.
     */
    int getType(ArgumentType* type, string name);
    
    
    /**
     * @brief Get value of the variable name stored in the respective register.
     * @param   value  Value that we want to set.
     * @param   name  Name of the variable to be set.
     * @return  If successful, 1, 0 otherwise.
     */
    int getValue(void* value, string name);
    
    /**
     * @brief Set value of the variable "name" to "value" if it's type is "type".
     * @param   value  Value, that we would like to set.
     * @param   type  Type of variable.
     * @param   name  Name of the variable that needs to be set.
     * @return  If successful, 0, error code otherwise.
     */
    int setValue(void* value, ArgumentType type, string name);
    
    /**
     * @brief Deletes the variable "name" from the respective register.
     * @param   name  Name of the variable to be cleared.
     * @return  If successful, 0, error code otherwise.
     */
    int deleteValue(string name);
    
    /**
     * @brief Checks if variable "name" exists in respective register.
     * @param   name  Name of the variable to be checked.
     * @return  If exists, true, false otherwise.
     */
    bool existsValue(string name);
    
    // Used so we can do deeper Unit Testing.
	friend class VariableRegisterTest;
};

#endif


#ifndef FILE_SpaceObjectRegister_SEEN
#define FILE_SpaceObjectRegister_SEEN

/****************************************************************************/
/* Includes                                                                 */
/****************************************************************************/
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include "SpaceObject.hh"
#include "VariableRegister.hh"
#include "ArgumentType.hh"

using namespace std;

/****************************************************************************/
/* Prototypes                                                               */
/****************************************************************************/

/**
 * @class SpaceObjectRegister
 * Class SpaceObjectRegister holds and allows to access variables, that are describing
 * space objects, encountered on the map.
 */

class SpaceObjectRegister {

private:
    // Private members
    vector<SpaceObject> Boulders;   /**< Vector of boulders. */
    vector<SpaceObject> Craters;    /**< Vector of craters. */
    vector<SpaceObject> Martians;   /**< Vector of martians. */
    VariableRegister* varsRegister; /**< Reference to VarRegister to access its variables */
    
	bool containsObject(SpaceObject *obj);
public:
    // Constructors and destructors
    /**
     * @brief Public constructor of the SpaceObjectRegister class.
     */
    SpaceObjectRegister(VariableRegister* varsReg);
    
    // Public methods
    /**
     * @brief Parse data and save encountered space objects.
     * @param   message  String to be parsed.
     * @return  If successful, 0, error code otherwise.
     */
    int parseSpaceObjects(string message);
    
    /**
     * @brief Clean all data stored in the register.
     * @return  If successful, 0, error code otherwise.
     */
    void clean();
    
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
     * @return  If successful, 0, error code otherwise.
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
	
	friend class SpaceObjectRegisterTest;
};

#endif


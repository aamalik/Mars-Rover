#ifndef FILE_MapRegister_SEEN
#define FILE_MapRegister_SEEN

/****************************************************************************/
/* Includes                                                                 */
/****************************************************************************/
#include <iostream>     
#include <string>
#include "SpaceObject.hh"

class SpaceObject;

using namespace std;

/****************************************************************************/
/* Prototypes                                                               */
/****************************************************************************/

/**
 * @class MapRegister
 * Class MapRegister holds and allows to access variables, that are describing
 * map.
 */

class MapRegister {
    
private:
    // Private members
    double length;  /**< Length of the map */
    double width;   /**< Width of the map */
    int timeLimit;  /**< Allowed time to complete the level */
    double drag;    /**<  Drag of the map */
    SpaceObject* homebase;  /**< Object for the homebase (0,0) */

public:
    // Constructors and destructors
    /**
     * @brief Public constructor of the Logger class.
     */
    MapRegister();
    
    /**
     * @brief Public destructor of the Logger class.
     */
    ~MapRegister();
    
    // Public methods
    /**
     * @brief   Method to parse details of the map.
     * @param   message String with message, that we want to parse.
     * @return  On success 0, error code otherwise.
     */
    int parseMapDetails(string message);
    
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
    
	friend class MapRegisterTest;
};

#endif


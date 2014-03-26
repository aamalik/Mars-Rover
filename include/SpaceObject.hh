#ifndef MarsXP2_SpaceObject_h
#define MarsXP2_SpaceObject_h

/****************************************************************************/
/* Includes                                                                 */
/****************************************************************************/
#include <iostream>
#include <string>
#include <sstream>
#include "Position.hh"
#include "ArgumentType.hh"

using namespace std;

/****************************************************************************/
/* Prototypes                                                               */
/****************************************************************************/

/**
 * @class SpaceObject
 * Class SpaceObject represents a custom object (crater/martian/boulder/homebase)
 * that can be encountered while browsing the map.
 */

class SpaceObject {
    
private:
    // Private members
    Position pos;   /**< Position of the object. */
    double radius;  /**< Radius of the object. */
    double speed;   /**< Speed of the object (set only for martians). */
    double heading; /**< Heading state of the object (set only for martians) */
    
public:
    // Constructors and destructors
    /**
     * @brief Public constructor of the SpaceObject class.
     */
    SpaceObject(string message);
    
    /**
     * @brief Public constructor of the SpaceObject class with set properties.
     * @param   x           x-coordinate of the object.
     * @param   y           y-coordinate of the object.
     * @param   radius      Radius of the object.
     * @param   speed       Speed of the object.
     * @param   heading     Status of where the object is heading.
     */
    SpaceObject(double x, double y, double radius, double speed, double heading);
    
    // Public methods
    /**
     * @brief Get type of the variable "name" stored in the registers.
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
	
	bool operator==(const SpaceObject &other);
	bool operator!=(const SpaceObject &other);
	
	friend class SpaceObjectTest;
	friend class SpaceObjectRegisterTest;
};

#endif

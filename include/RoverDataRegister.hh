#ifndef FILE_RoverDataRegister_SEEN
#define FILE_RoverDataRegister_SEEN

/****************************************************************************/
/* Includes                                                                 */
/****************************************************************************/
#include <iostream>
#include <string>
#include <sstream>
#include "ArgumentType.hh"
#include "Position.hh"

using namespace std;

/****************************************************************************/
/* Prototypes                                                               */
/****************************************************************************/

/**
 * @class RoverDataRegister
 * Class RoverDataRegister holds and allows to access variables, that are describing
 * rover.
 */

class RoverDataRegister {

private:
    // Private members
    Position pos;       /**< Position of the rover. */
    int speedState;     /**< Current speed state of the rover. */
    int turningState;   /**< Current turning state of the rover. */
    double radius;      /**< Radius of the rover. */
    double speed;       /**< Speed of the rover. */
    double heading;     /**< Where rover is heading. */
    double minSensor;   /**< Minimal vision sensor. */
    double maxSensor;   /**< Maximum vision sensor. */
    double maxSpeed;    /**< Maximum speed. */
    double maxTurn;     /**< Maximum turning angle. */
    double maxHardTurn; /**< Maximum hard-turning angle. */
    
public:
    // Constructors and destructors
    /**
     * @brief Public constructor of the RoverDataRegister class.
     */
    RoverDataRegister();
    
    // Public methods
    /**
     * @brief Parse initial data and construct described rover.
     * @param   message  String to be parsed.
     * @return  If successful, 0, error code otherwise.
     */
    int init(string message);
    
    /**
     * @brief Parse data and update rover details respectively.
     * @param   message  String to be parsed.
     * @return  If successful, 0, error code otherwise.
     */
    int parseRover(string message);
    
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
	
	friend class RoverDataRegisterTest;
};

#endif


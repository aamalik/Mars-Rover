#ifndef MarsXP2_Position_h
#define MarsXP2_Position_h
#include <ostream>

/****************************************************************************/
/* Prototypes                                                               */
/****************************************************************************/

/**
 * @class Position
 * Class Position represents (x,y) coordinates of objects on the map.
 */

class Position {
	
	friend std::ostream& operator<< (std::ostream& stream, const Position& p);
	
  
private:
    // Private members
    double x;   /**< x-coordinate. */
    double y;   /**< y-coordinate. */
    
public:
    // Constructors and destructors
    /**
     * @brief Public constructor of the Position class.
     */
    Position();
	
	bool operator==(const Position &other);
	bool operator!=(const Position &other);

    Position operator=(const Position &other);
    /**
     * @brief Public constructor of the Position class with set properties.
     * @param   x   x-coordinate
     * @param   y   y-coordinate
     */
    Position(double x, double y);
    
    // Public methods
    /**
     * @brief Setter method for x-coordinate.
     * @param   aX  x-coordinate to be set.
     */
    void setX(double aX);
    
    /**
     * @brief Setter method for y-coordinate.
     * @param   aY  y-coordinate to be set.
     */
    void setY(double aY);
    
    /**
     * @brief Getter method for x-coordinate.
     * @return  Returns x-coordinate.
     */
    double getX();
    
    /**
     * @brief Getter method for y-coordinate.
     * @return  Returns y-coordinate.
     */
    double getY();
    
};

#endif

/****************************************************************************/
/* Includes                                                                 */
/****************************************************************************/
#include "SpaceObject.hh"
#include <cstdlib>
#include <cstdio>

/****************************************************************************/
/* Implementation                                                           */
/****************************************************************************/

//this constructor is never used, it is just here to comply with the design.
//this happens in SpaceObjectRegister::parseSpaceObjects
SpaceObject::SpaceObject(string message) {
    
    istringstream ss(message);
    double x,y;
    char c;
    
    ss >> c;
    
    switch (c) {
        case 'b':
        case 'c':
        case 'h':
            ss >> x >> y >> this->radius;
            this->pos.setX(x);
            this->pos.setY(y);
            this->speed = 0;
            this->heading = 0;
#ifdef DEBUG
            cout << "Parsed a static object with x: " << x << " and y: " << y << " and radius: " << radius << endl;
#endif
            break;
            
        case 'm':
            ss >> x >> y >> this->radius >> this->speed >> this->heading;
            this->pos.setX(x);
            this->pos.setY(y);
#ifdef DEBUG
            cout << "Parsed martian with x: " << x << ", y: " << y << " ,radius: " << this->radius << "Speed: " << this->speed << " ,heading: " << this->heading << endl;
#endif
            break;
            
        default:
            perror("Parsing failed!");
            break;
    }
    
    if (ss.fail())
        perror("Parsing failed!");
}

SpaceObject::SpaceObject(double x, double y, double radius, double speed, double heading) {
    
    pos.setX(x);
    pos.setY(y);
    this->radius = radius;
    this->speed = speed;
    this->heading = heading;
}

int SpaceObject::getType(ArgumentType* type, string name) {
    if (name.compare("Position") == 0)
        *type = POSITION;
    else if (name.compare("Radius") == 0 || name.compare("Speed") == 0 || name.compare("Heading") == 0 || name.compare("X") == 0 || name.compare("Y") == 0)
        *type = DOUBLE;
    else return 1; //Smth went wrong.
    
    return 0;
}

int SpaceObject::getValue(void* value, string name) {
    
    if (name.compare("Position") == 0)
        *(Position*)value = this->pos;
    else if (name.compare("Radius") == 0)
        *(double*)value = this->radius;
    else if (name.compare("Speed") == 0)
        *(double*)value = this->speed;
    else if (name.compare("Heading") == 0)
        *(double*)value = this->heading;
		else if (name.compare("X") == 0)
			*(double*)value = this->pos.getX();
		else if (name.compare("Y") == 0)
			*(double*)value = this->pos.getY();
    else return 1; // Smth went wrong.
    
    return 0;
}

int SpaceObject::setValue(void* value, ArgumentType type, string name) {
    
		if (name.compare("Position") == 0 && type == POSITION) {
			this->pos = *(Position*)value;
		}
    else if (name.compare("Radius") == 0 && type == DOUBLE)
        this->radius = *(double*)value;
    else if (name.compare("Speed") == 0 && type == DOUBLE)
        this->speed = *(double*)value;
    else if (name.compare("Heading") == 0 && type == DOUBLE)
			this->heading = *(double*)value;
		else if (name.compare("X") == 0 && type == DOUBLE)
			this->pos.setX(*(double*)value);
		else if (name.compare("Y") == 0 && type == DOUBLE)
			this->pos.setY(*(double*)value);
    else return 1; // Smth went wrong.
    
    return 0;
}

bool SpaceObject::operator==(const SpaceObject &other) {
#ifdef DEBUG
	cerr << "Comparing SpaceObjects... Properties are pos: "<<this->pos<<"?="<<other.pos << ", "<<this->radius<<"?="<<other.radius << endl;
	cerr << "Comparing SpaceObjects(2) Properties are heading: "<<this->heading<<"?="<<other.heading << ", "<<this->speed<<"?="<<other.speed << endl;
#endif
	return (this->pos == other.pos) && (this->heading == other.heading) && (this->speed == other.speed) && (this->radius == other.radius);
}

bool SpaceObject::operator!=(const SpaceObject &other) {
	return !(*this == other);
}

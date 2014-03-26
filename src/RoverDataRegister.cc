/****************************************************************************/
/* Includes                                                                 */
/****************************************************************************/
#include "RoverDataRegister.hh"
#include <cstdlib>
#include <cstdio>
#include "Position.hh"

/****************************************************************************/
/* Implementation                                                           */
/****************************************************************************/

RoverDataRegister::RoverDataRegister() {
    
    this->radius = 0.5;
    this->pos.setX(0);
    this->pos.setY(0);
    this->speedState = 2;
    this->turningState = 3;
    this->heading = 0;
    this->minSensor = 0;
    this->maxSensor = 0;
    this->maxSpeed = 0;
    this->maxTurn = 0;
    this->maxHardTurn = 0;
}

int RoverDataRegister::init(string message) {
    
    istringstream ss(message);
	
  
#ifdef DEBUG
	cerr << "Recieved rover init string: "<< message << endl;
#endif
	
    ss >> this->minSensor >> this->maxSensor >> this->maxSpeed >> this->maxTurn >> this->maxHardTurn;
    
    if (ss.fail()) {
        perror("Failed parsing rover's init message. Stream error");
        return 1;
    }
	char dummy = 0;
    ss >> dummy;
	if (dummy != ';') {
		perror("Failed parsing rover's init message. Expected ';'");
		return 1;
	}
    
#ifdef DEBUG
    cout << "Initialized rover with minSensor: " << this->minSensor << " ,maxSensor: " << this->maxSensor << " ,maxSpeed: " << this->maxSpeed << " ,maxTurn: " << this->maxTurn << ", maxHardTurn: " << this->maxHardTurn << endl;
#endif
    
    return 0;
}

int RoverDataRegister::parseRover(string message) {
    
#ifdef DEBUG
	cerr << "Recieved rover details string: "<< message << endl;
#endif
	
    istringstream ss(message);
    double x,y;
    char sState,tState;
     
    ss >> sState >> tState >> x >> y >> this->heading >> this->speed;
    
	if(ss.fail()) {
        perror("Failed parsing rover data. Stream error");
			return 1;
		}
		
    
    this->pos.setX(x);
    this->pos.setY(y);
    
    switch (sState) {
        case 'b':
            this->speedState = 1;
            break;
        case '-':
            this->speedState = 2;
            break;
        case 'a':
            this->speedState = 3;
            break;
		default:
			perror("Failed parsing rover data. Invalid acceleration state");
			return 1;
    }
    
    switch (tState) {
        case 'L':
            this->turningState = 1;
            break;
        case 'l':
            this->turningState = 2;
            break;
        case '-':
            this->turningState = 3;
            break;
        case 'r':
            this->turningState = 4;
            break;
        case 'R':
            this->turningState = 5;
            break;
			default:
				perror("Failed parsing rover data. Invalid turn state");
				return 1;
    }
    
#ifdef DEBUG
    cout << "Parsed rover data with x: " << x << " ,y: " << y << " ,speedState: " << sState << " ,turnState: " << tState << ", heading: " << this->heading << " ,speed: " << this->speed << endl;
#endif
    
     return 0;

}

void RoverDataRegister::clean() {
    
    this->radius = 0.5;
    this->pos.setX(0);
    this->pos.setY(0);
    this->speedState = 2;
    this->turningState = 3;
    this->radius = 0;
    this->heading = 0;
    this->minSensor = 0;
    this->maxSensor = 0;
    this->maxSpeed = 0;
    this->maxTurn = 0;
    this->maxHardTurn = 0;
}

int RoverDataRegister::getType(ArgumentType* type, string name) {
    if (name.find("Rover") != 0) {
        return -1;
    }
    if (name.length() == 5) {
        *type = ROVER;
        return 0;
    } 

    if (name.find(".") != 5) {
        return -1;
    }
    string parameter = name.substr(6);
    if (parameter.compare("Radius") == 0 || 
        parameter.compare("Speed") == 0 || 
        parameter.compare("Heading") == 0 || 
        parameter.compare("MinSensor") == 0 || 
        parameter.compare("MaxSensor") == 0 || 
        parameter.compare("MaxSpeed") == 0 || 
        parameter.compare("MaxTurn") == 0 || 
        parameter.compare("MaxHardTurn") == 0)
        *type = DOUBLE;
    else if (parameter.compare("SpeedState") == 0 || 
        parameter.compare("TurningState") == 0)
        *type = INT;
    else if (parameter.compare("Position") == 0)
        *type = POSITION;
    else return 1; //Smth went wrong
    
    return 0;
}

int RoverDataRegister::getValue(void* value, string name) {
    if (name.find("Rover") != 0 || name.length() <= 6) {
        return -1;
    } 
    if (name.find(".") != 5) {
        return -1;
    }
    string parameter = name.substr(6);
    
    if (parameter.compare("Radius") == 0)
        *(double*)value = this->radius;
    else if (parameter.compare("Speed") == 0)
        *(double*)value = this->speed;
    else if (parameter.compare("Heading") == 0)
        *(double*)value = this->heading;
    else if (parameter.compare("MinSensor") == 0)
        *(double*)value = this->minSensor;
    else if (parameter.compare("MaxSensor") == 0)
        *(double*)value = this->maxSensor;
    else if (parameter.compare("MaxSpeed") == 0)
        *(double*)value = this->maxSpeed;
    else if (parameter.compare("MaxTurn") == 0)
        *(double*)value = this->maxTurn;
    else if (parameter.compare("MaxHardTurn") == 0)
        *(double*)value = this->maxHardTurn;
    else if (parameter.compare("SpeedState") == 0)
        *(int*)value = this->speedState;
    else if (parameter.compare("TurningState") == 0)
        *(int*)value = this->turningState;
    else if (parameter.compare("Position") == 0)
        *(Position*)value = this->pos;
    else return 1; //Smth went wrong
    
    return 0;

}

int RoverDataRegister::setValue(void* value, ArgumentType type, string name) {
    if (name.find("Rover") != 0) {
        return -1;
    } 
    if (name.length() == 5) {
        type = ROVER;
    } else {
        if (name.find(".") != 5) {
            return -1;
        }
    }
    string parameter = name.substr(6);
    
    if (parameter.compare("Radius") == 0 && type == DOUBLE)
        this->radius = *(double*)value;
    else if (parameter.compare("Speed") == 0 && type == DOUBLE)
        this->speed = *(double*)value;
    else if (parameter.compare("Heading") == 0 && type == DOUBLE)
        this->heading = *(double*)value;
    else if (parameter.compare("SpeedState") == 0 && type == INT)
        this->speedState = *(int*)value;
    else if (parameter.compare("TurningState") == 0 && type == INT)
        this->turningState = *(int*)value;
    else if (parameter.compare("Position") == 0 && type == POSITION)
        this->pos = *(Position*)value;
    else return 1; //Smth went wrong
    
    return 0;
}
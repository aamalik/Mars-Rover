/****************************************************************************/
/* Includes                                                                 */
/****************************************************************************/
#include "MapRegister.hh"
#include <cstdlib>
#include <cstdio>

/****************************************************************************/
/* Implementation                                                           */
/****************************************************************************/

MapRegister::MapRegister() {
    
    this->homebase = new SpaceObject(0,0,5,0,0);
    this->length = 0;
    this->width = 0;
    this->timeLimit = 0;
    this->drag = -1;
}

MapRegister::~MapRegister() {
    delete homebase;
}

int MapRegister::parseMapDetails(string message) {
  
#ifdef DEBUG
	cerr << "Recieved map details string: "<< message << endl;
#endif
	
    istringstream ss(message);
    ss >> this->width >> this->length >> this->timeLimit;
		
	if (this->timeLimit <= 0) {
		perror("Parsing of map details failed. TimeLimit has to be positive");
		return 1;
	}
    
    if (ss.fail()) {
        perror("Parsing of map details failed");
        return 1;
    }
    
#ifdef DEBUG
    cout << "Parsed map details: length(" << this->length << "), width(" << this->width << "), timelimit(" << this->timeLimit << ")." << endl;
#endif
    return 0;
}

int MapRegister::getType(ArgumentType* type, string name) {

    if (name.find("Map.") != 0) {
        return -1;
    }
    string attribute = name.substr(4);
    if (attribute.compare("Length") == 0 || attribute.compare("Width") == 0 || attribute.compare("Drag") == 0)
        *type = DOUBLE;
    else if (attribute.compare("TimeLimit") == 0)
        *type = INT;
    else { 
        if (attribute.find("Homebase") != 0)
            return 1;
        string attr = attribute.substr(9);
        return homebase->getType(type,attr);
    }
    
    return 0;
}

int MapRegister::getValue(void* value, string name) {
    
    if (name.find("Map.") != 0) {
        return -1;
    }
    string attribute = name.substr(4);

    if (attribute.compare("Length") == 0)
        *(double*)value = this->length;
    else if (attribute.compare("Width") == 0)
        *(double*)value = this->width;
    else if (attribute.compare("TimeLimit") == 0)
        *(int*)value = this->timeLimit;
    else if (attribute.compare("Drag") == 0)
        *(double*)value =this->drag;
    else {
        if (attribute.find("Homebase") != 0)
            return 1;

        string attr = attribute.substr(9);
        return homebase->getValue(value, attr);
    }   
    
    return 0;
}

int MapRegister::setValue(void* value, ArgumentType type, string name) {
    
    if (name.find("Map.") != 0) {
        return -1;
    }
    string attribute = name.substr(4);
    if (attribute.compare("Length") == 0 && type == DOUBLE)
        this->length = *(double*)value;
    else if (attribute.compare("Width") == 0 && type == DOUBLE)
        this->width = *(double*)value;
    else if (attribute.compare("TimeLimit") == 0 && type == INT) {
				if (*(int*)value <= 0)
					return 1;
        this->timeLimit = *(int*)value;
		}
    else if (attribute.compare("Drag") == 0 && type == DOUBLE)
        this->drag = *(double*)value;
    else {
        if (attribute.find("Homebase") != 0)
            return 1;
        string attr = attribute.substr(9);
        return homebase->setValue(value, type, attr);
    }
    
    return 0;
}
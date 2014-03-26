/****************************************************************************/
/* Includes                                                                 */
/****************************************************************************/
#include "SpaceObjectRegister.hh"
#include <cstdlib>
#include <cstdio>
#include <algorithm>

/****************************************************************************/
/* Implementation                                                           */
/****************************************************************************/

static string getIndex(string name) {
    if (name.find("[") == string::npos || name.find("]") == string::npos) 
        return "";

    int getBr1 = name.find("[");
    int getBr2 = name.find("]");

    string index = name.substr(getBr1+1, getBr2 - getBr1 - 1);

    return index;
}

SpaceObjectRegister::SpaceObjectRegister(VariableRegister* varsReg) {
    
    this->varsRegister = varsReg;
}

int SpaceObjectRegister::parseSpaceObjects(string message) {
    
    Boulders.clear();
    Craters.clear();
    Martians.clear();

#ifdef DEBUG
	cerr << "Recieved object details string: "<< message << endl;
#endif

    istringstream ss(message);
    double x,y,radius,speed,heading;
    char c;
    
    while (ss >> c) {
        
        switch (c) {
            case 'b':
                ss >> x >> y >> radius;
                speed = 0;
                heading = 0;
                Boulders.push_back( SpaceObject(x,y,radius,speed,heading) );
                break;
                
            case 'c':
                ss >> x >> y >> radius;
                speed = 0;
                heading = 0;
                Craters.push_back( SpaceObject(x,y,radius,speed,heading) );
                break;
                
            case 'h':
                ss >> x >> y >> radius;
                break;
                
            case 'm':
                ss >> x >> y >> speed >> heading;
                Martians.push_back( SpaceObject(x,y, 0.5,speed,heading) );
                break;
			case ';': 
				break;
        
            case ' ':
                continue;

            default:
            {
                perror("Parsing failed! Unknown object type.");
                return 1;
            }
                break;
        }
			
			if (message[message.size()-1] != ';') {
				perror("Parsing failed. String not terminated.");
				return 1;
			}
        
			if (ss.fail()) {
					perror("Parsing failed! Stream error.");
					return 1;
			}
    }
		return 0;
}

void SpaceObjectRegister::clean() {
    
    Boulders.clear();
    Craters.clear();
    Martians.clear();
}

int SpaceObjectRegister::getType(ArgumentType* type, string name) {
    
    //Assume input of, for.ex. Boulder[i].radius
    //Where Boulder = object, i = index from varregister, radius = property (possibly empty).
	string subElement;
    int ret;
    ArgumentType iType = NOTYPE;
    string iStr = getIndex(name);
    if (iStr == "")
        return 1;

    int val = -1;
    istringstream converter(iStr);
    if (!(converter >> val) && converter.tellg() != (int) iStr.size()) {
        ret = varsRegister->getType(&iType,iStr);
        if (ret != 0)
            return 1;
        if (iType != INT)
            return 1; // bad index
        ret = varsRegister->getValue(&val, iStr);
        if (ret != 0) 
            return 1;
    }
    if (val < 0)
        return 1; //bad index
    size_t index = val;

#ifdef DEBUG
    cout << "Given name: " << name << ". Extracted index: " << iStr << ". Desired int value from VariableRegister: " << index << endl;
#endif
	
    if (name.find("Boulder") != string::npos) {
			if (index > Boulders.size()-1)
				return 1; //bad index
			if (name[name.size()-1] == ']')
					*type = BOULDER;
			else {
				subElement = name.substr(name.find(".")+1);
#ifdef DEBUG
				cerr << "Extracted property's name: " << subElement << " (size = " << subElement.size()<< ")" << endl;
#endif
					if (Boulders[index].getType(type,subElement))
							return 2; //can't access the property
			}
    }
    else if (name.find("Crater") != string::npos) {
				if (index > Craters.size()-1)
					return 1; //bad index
        if (name[name.size()-1] == ']')
            *type = CRATER;
        else {
            
            if (Craters[index].getType(type,name.substr(name.find(".")+1)) != 0)
                return 2; //can't access the property
        }
    }
    else if (name.find("Martian") != string::npos) {
				if (index > Martians.size()-1)
					return 1; //bad index
        if (name[name.size()-1] == ']')
            *type = MARTIAN;
        else {
            if (Martians[index].getType(type,name.substr(name.find(".")+1)) != 0)
                return 2; //can't access the property
        }
    }
	else
		return -1;
    
    return 0;
}

int SpaceObjectRegister::getValue(void* value, string name) {
    
    int ret;
    ArgumentType iType = NOTYPE; 
    string iStr = getIndex(name);
    if (iStr == "")
        return 1;

    int val = -1;
    istringstream converter(iStr);
    if (!(converter >> val) && converter.tellg() != (int) iStr.size()) {
        ret = varsRegister->getType(&iType,iStr);
        if (ret != 0)
            return 1;
        if (iType != INT)
            return 1; // bad index
        ret = varsRegister->getValue(&val, iStr);
        if (ret != 0) 
            return 1;
    }
    if (val < 0)
        return 1; //bad index
    size_t index = val;
    
#ifdef DEBUG
    cout << "Given name: " << name << ". Extracted index: " << iStr << ". Desired int value from VariableRegister: " << index << endl;
#endif
    
    if (name.find("Boulder") != string::npos) {
				if (index > Boulders.size()-1)
					return 1; //bad index
        if (name[name.size()-1] == ']')
            *(SpaceObject*)value = Boulders[index];
        else {
            if (Boulders[index].getValue(value,name.substr(name.find(".")+1)) != 0)
                return 2; //can't access the property
        }
    }
    else if (name.find("Crater") != string::npos) {
				if (index > Craters.size()-1)
					return 1; //bad index
        if (name[name.size()-1] == ']')
            *(SpaceObject*)value = Craters[index];
        else {
            
            if (Craters[index].getValue(value,name.substr(name.find(".")+1)) != 0)
                return 2; //can't access the property
        }
    }
    else if (name.find("Martian") != string::npos) {
			if (index > Martians.size()-1)
				return 1; //bad index
        if (name[name.size()-1] == ']')
            *(SpaceObject*)value = Martians[index];
        else {
            if (Martians[index].getValue(value,name.substr(name.find(".")+1)) != 0)
                return 2; //can't access the property
        }
    } else {
        return 1;
    }
    return 0;
}

int SpaceObjectRegister::setValue(void* value, ArgumentType type, string name) {
    
    int ret;
    ArgumentType iType = NOTYPE; 
    string iStr = getIndex(name);
    if (iStr == "")
        return 1;

    int val = -1;
    istringstream converter(iStr);
    if (!(converter >> val) && converter.tellg() != (int) iStr.size()) {
        ret = varsRegister->getType(&iType,iStr);
        if (ret != 0)
            return 1;
        if (iType != INT)
            return 1; // bad index
        ret = varsRegister->getValue(&val, iStr);
        if (ret != 0) 
            return 1;
    }
    if (val < 0)
        return 1; //bad index
	size_t index = val;
    
#ifdef DEBUG
    cout << "Given name: " << name << ". Extracted index: " << iStr << ". Desired int value from VariableRegister: " << index << endl;
#endif
    
    if (name.find("Boulder") != string::npos) {
		if (index > Boulders.size()-1)
			return 1; //bad index
        if (name[name.size()-1] == ']')
            Boulders[index] = *(SpaceObject*)value;
        else {
            if (Boulders[index].setValue(value,type,name.substr(name.find(".")+1)) != 0)
                return 2; //can't access the property
        }
    }
    else if (name.find("Crater") != string::npos) {
				if (index > Craters.size()-1)
					return 1; //bad index
        if (name[name.size()-1] == ']')
            Craters[index] = *(SpaceObject*)value;
        else {
            
            if (Craters[index].setValue(value,type,name.substr(name.find(".")+1)) != 0)
                return 2; //can't access the property
        }
    }
    else if (name.find("Martian") != string::npos) {
				if (index > Martians.size()-1)
					return 1; //bad index
        if (name[name.size()-1] == ']')
            Martians[index] = *(SpaceObject*)value;
        else {
            if (Martians[index].setValue(value,type,name.substr(name.find(".")+1)) != 0)
                return 2; //can't access the property
        }
    } else {
        return 1;
    }
    
    return 0;
}

bool SpaceObjectRegister::containsObject(SpaceObject *obj) {
	return (std::find(Boulders.begin(), Boulders.end(), *obj) != Boulders.end() ||
					std::find(Craters.begin(), Craters.end(), *obj) != Craters.end() ||
					std::find(Martians.begin(), Martians.end(), *obj) != Martians.end());
	
}
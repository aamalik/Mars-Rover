/****************************************************************************/
/* Includes                                                                 */
/****************************************************************************/
#include "../include/MemoryHandler.hh"      // MemoryHandler class definition

/****************************************************************************/
/* Implementation                                                           */
/****************************************************************************/

MemoryHandler::MemoryHandler() {
    this->spaceObjects = new SpaceObjectRegister(&variables);
    ctime = 0;
}

MemoryHandler::~MemoryHandler() {
    delete this->spaceObjects;
}

int MemoryHandler::init(string message) {
	if (message.size() <= 0 || message.at(0) != 'I' || message[message.size()-1] != ';'){
		perror("Parsing init message failed. Invalid message format");
		return 1;
	}
	istringstream ss(message);
	ostringstream os;
	double d1, d2, d3;
	char type;
	string msg;
	ss >> type >> d1 >> d2 >> d3;
	if (ss.fail()) {
		perror("Parsing init message failed. Stream error");
		return 1;
	}
	getline(ss, msg);
	os << d1 << " " << d2 << " " << d3;
	if(this->rover.init(msg)) {
		perror("Parsing init message failed. Rover init fail");
		return 1;
	}
		
	if (this->map.parseMapDetails(os.str())) {
		perror("Parsing init message failed. Map init fail");
		return 1;
	}
	return 0;
}

int MemoryHandler::parseData(std::string message) {
	istringstream ss(message);
	ostringstream os;
	char type;
	double i2, i3, i4, i5;
	char c1, c2;
	double dtime;
	string msg;
  switch (message.at(0)) {
		case 'I':
			this->init(message);
			break;
		case 'T':
			if (!(ss >> type >> dtime >> c1 >> c2 >> i2 >> i3 >> i4 >> i5 )) {
				return 1;
			}
			this->ctime = static_cast<int> (dtime);
			getline(ss, msg);
			if (!(os << c1 << c2 << " " << i2  << " " << i3 << " " << i4 << " " << i5)) {
				return 1;
			}
			if(spaceObjects->parseSpaceObjects(msg))
				return 1;
			if (rover.parseRover(os.str()))
				return 1;
			break;

		default:
			//other messages can be ignored for now
			return 1;
	}
	return 0;
}

int MemoryHandler::clean() {
	//some of them return void, some int. should we make that more uniform?
	spaceObjects->clean();
	rover.clean();
	
	if(variables.clean())
		return 1;
	return 0;
}

int MemoryHandler::cleanDynamicData() {
	
	if(variables.clean())
		return 1;
	return 0;
}


int MemoryHandler::getType(ArgumentType* type, std::string name) {
	if(name.compare("CurrentTime") == 0) {
		*type = INT;
		return 0;
	}
	if(!variables.getType(type, name))
		return 0;
	if(!map.getType(type, name))
		return 0;
	if(!spaceObjects->getType(type, name))
		return 0;
	if(!rover.getType(type, name))
		return 0;
	if(!Parser::parseGetTypeImmediate(type,name))
		return 0;
	return 1;
}


int MemoryHandler::getValue(void* value, std::string name) {
	if(name.compare("CurrentTime") == 0) {
		*((int*)value) = this->ctime;
		return 0;
	}
	if(!variables.getValue(value, name))
		return 0;
	if(!map.getValue(value, name))
		return 0;
	if(!spaceObjects->getValue(value, name))
		return 0;
	if(!rover.getValue(value, name))
		return 0;
	if(!Parser::parseImmediate(value,name))
		return 0;
	return 1;
}

int MemoryHandler::setValue(void* value, ArgumentType type, std::string name) {
	if (value == NULL)
		return variables.setValue(value, type, name);

	if(name.compare("CurrentTime") == 0)
		return 1; //CurrentTime is read only, forwarding would create a variable by that name otherwise
	if(!map.setValue(value, type, name))
		return 0;
	if(!spaceObjects->setValue(value, type, name))
		return 0;
	if(!rover.setValue(value, type, name))
		return 0;
	if(!variables.setValue(value, type, name))
		return 0;
	return 1;
}


int MemoryHandler::deleteValue (std::string name) {
	//correct me if i'm wrong, but I think only Variables can be deleted
	return variables.deleteValue(name);
}

void MemoryHandler::setReturnString(std::string aReturnString) {
	returnString = aReturnString;
}

string MemoryHandler::getReturnString() {
	return returnString;
}
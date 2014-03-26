/****************************************************************************/
/* Includes                                                                 */
/****************************************************************************/
#include "VariableRegister.hh"
#include <cstdlib>
#include <cstdio>
#include <cctype>

/****************************************************************************/
/* Implementation                                                           */
/****************************************************************************/

enum {
    NORMAL,
    ALLOWCOLON
};

static int isGoodVariableName(string name,int type) {

    // types allowed:
    // [a-zA-Z][a-zA-Z0-9]* \[ [a-zA-Z0-9]* \]
    // OR if type == ALLOWCOLON
    // [a-zA-Z][a-zA-Z0-9]* : [0-9]*

    int p1,p2,sc;
    p1 = p2 = sc = 0;

    if (!(isupper(name[0]) || islower(name[0]))) {
        return 1;
    }

    for(unsigned int i = 1; i < name.size(); ++i) {
        if (isdigit(name[i]) || isupper(name[i]) || islower(name[i])) {
            if (sc > 0 && !isdigit(name[i]))
                return 1;
            else ;
            // do nothing 
        } else if (name[i] == '[' && !p1) {
            p1 = i;
        } else if (name[i] == ']' && !p2) {
            p2 = i;
        } else if (name[i] == ':' && !sc) {
            if (ALLOWCOLON == type)
                sc = i;
            else 
                return 1;
        } else 
            return 1;
    }

    if (p1 > 0 && sc > 0)
        return 1;

    if (!p1 && !p2)
        return 0;

    if (!(p1 > 0 && p1 < p2 && (unsigned int) p2 == name.size()-1))
        return 1;

    return 0;
}

VariableRegister::VariableRegister() {
    // Useless XP2 Code
    this->intMap.clear();
    this->doubleMap.clear();
    this->stringMap.clear();
    this->positionMap.clear();
    this->intArrayMap.clear();
    this->doubleArrayMap.clear();
    this->stringArrayMap.clear();
    this->positionArrayMap.clear();
}

int VariableRegister::clean() {
    
    this->intMap.clear();
    this->doubleMap.clear();
    this->stringMap.clear();
    this->positionMap.clear();
    this->intArrayMap.clear();
    this->doubleArrayMap.clear();
    this->stringArrayMap.clear();
    this->positionArrayMap.clear();
    
    return 0;
}

int VariableRegister::getType(ArgumentType* type, string name) {
    
    if (isGoodVariableName(name,NORMAL)) // Sanity check
        return 1;

    int idx = -1;
    int idx_start_pos = name.find("[");
    int idx_end_pos = name.find("]");
    int hasIndex = 0;
    if (idx_start_pos != (int) string::npos && idx_end_pos != (int) string::npos) {
        hasIndex = 1;
        string index_str = name.substr(idx_start_pos+1, idx_end_pos - idx_start_pos - 1);
        istringstream converter(index_str);
        if (!(converter >> idx) && converter.tellg() != (int) index_str.size()) {
            ArgumentType type;
            int ret = getType(&type,index_str);
            if (ret != 0 && type != INT) {
                return -1;
            }
            ret = getValue(&idx,index_str);
            if (ret != 0) {
                return ret;
            }
        }
        name = name.substr(0,idx_start_pos);
    } else if (idx_start_pos != (int) string::npos || idx_end_pos != (int) string::npos) {
        return 1;
    }
    if (intMap.find(name) != intMap.end())
        if (!hasIndex)
            *type = INT;
        else 
            return 1;
    else if (doubleMap.find(name) != doubleMap.end())
        if (!hasIndex)
            *type = DOUBLE;
        else 
            return 1;
    else if (stringMap.find(name) != stringMap.end())
        if (!hasIndex) 
            *type = STRING;
        else 
            return 1;
    else if (positionMap.find(name) != positionMap.end())
        if (!hasIndex) 
            *type = POSITION;
        else 
            return 1;
    else if (intArrayMap.find(name) != intArrayMap.end())
        if (hasIndex) {
            if (idx >= 0 && (unsigned int)idx < intArrayMap[name].size() )
                *type = INT;
            else 
                return 1;
        } else
            *type = INTARRAY;
    else if (doubleArrayMap.find(name) != doubleArrayMap.end())
        if (hasIndex){
            if (idx >= 0 && (unsigned int)idx < doubleArrayMap[name].size() )
                *type = DOUBLE;
            else 
                return 1;
        }
        else 
            *type = DOUBLEARRAY;
    else if (stringArrayMap.find(name) != stringArrayMap.end())
        if (hasIndex) {
            if (idx >= 0 && (unsigned int)idx < stringArrayMap[name].size() )
                *type = STRING;
            else 
                return 1;
        } else 
            *type = STRINGARRAY;
    else if (positionArrayMap.find(name) != positionArrayMap.end())
        if (hasIndex) {
            if (idx >= 0 && (unsigned int)idx < positionArrayMap[name].size() )
                *type = POSITION;
            else 
                return 1;
        } else
            *type = POSITIONARRAY;
    else return 1; //Didn't find variable.
    
    return 0;
}

int VariableRegister::getValue(void* value, string name) {
    
    if (isGoodVariableName(name,NORMAL)) // Sanity check
        return 1;

    int idx = -1; 
    int idx_start_pos = name.find("[");
    int idx_end_pos = name.find("]");
    if (idx_start_pos != (int) string::npos && idx_end_pos != (int) string::npos) {
        string index_str = name.substr(idx_start_pos+1, idx_end_pos - idx_start_pos - 1);
        istringstream converter(index_str);
        if (!(converter >> idx) && converter.tellg() != (int) index_str.size()) {
            ArgumentType type;
            int ret = getType(&type,index_str);
            if (ret != 0 && type != INT) {
                return -1;
            }
            ret = getValue(&idx,index_str);
            if (ret != 0) {
                return ret;
            }
        }
        name = name.substr(0, idx_start_pos);
    } else if (idx_start_pos != (int) string::npos || idx_end_pos != (int) string::npos) {
        return -1;
    }

    if (intMap.find(name) != intMap.end())
        *((int*)value) = intMap[name];
    else if (doubleMap.find(name) != doubleMap.end())
        *((double*)value) = doubleMap[name];
    else if (stringMap.find(name) != stringMap.end())
        *((string*)value) = stringMap[name];
    else if (positionMap.find(name) != positionMap.end())
        *((Position*)value) = positionMap[name];
    else if (intArrayMap.find(name) != intArrayMap.end()) {
        if (idx >= 0 && idx < (int) intArrayMap[name].size()) {
            *(int*) value = intArrayMap[name][idx];
        } else {
            return 1;
        }
    } else if (doubleArrayMap.find(name) != doubleArrayMap.end()) {
        if (idx >= 0 && idx < (int) doubleArrayMap[name].size()) {
            *(double*) value = doubleArrayMap[name][idx];
        } else {
            return 1;
        }
    } else if (stringArrayMap.find(name) != stringArrayMap.end()){
        if (idx >= 0 && idx < (int) stringArrayMap[name].size()) {
            *(string*) value = stringArrayMap[name][idx];
        } else {
            return 1;
        }
    } else if (positionArrayMap.find(name) != positionArrayMap.end()){
        if (idx >= 0 && idx < (int) positionArrayMap[name].size()) {
            *(Position*) value = positionArrayMap[name][idx];
        } else {
            return 1;
        }
    } else return 1; //Didn't find variable.
    
    return 0;
}

int VariableRegister::setValue(void* value, ArgumentType type, string name) {
    
    if (isGoodVariableName(name,ALLOWCOLON)) // Sanity check
        return 1;

    // If we create a new array we get value as NULL and the name will be of type: [vector-name]:[vector-size]

    if (value == NULL) {
        int size;
        int size_pos = name.find(":");
        if (size_pos == (int) string::npos) {
            return 1;
        }
        string array_name = name.substr(0, size_pos);
        string size_str = name.substr(size_pos+1);
        istringstream size_stream(size_str);
        if (!(size_stream >> size)) {
            return 1;
        }
        if (type == INT) {
                vector<int> newIntArray;
                newIntArray.resize(size, 0);
                intArrayMap[array_name] = newIntArray;
                return 0;
        } else if (type == DOUBLE) {
                vector<double> newDoubleArray;
                newDoubleArray.resize(size, 0);
                doubleArrayMap[array_name] = newDoubleArray;
                return 0;
        } else if (type == POSITION) {
                vector<Position> newPositionArray;
                newPositionArray.resize(size, Position(0,0));
                positionArrayMap[array_name] = newPositionArray;
                return 0;
        } else if (type == STRING) {
                vector<string> newStringArray;
                newStringArray.resize(size, "");
                stringArrayMap[array_name] = newStringArray;
                return 0;
        } else {
                return 1;
        }

        return 0;
    }

    // If we are setting a value 

    int idx = -1;
    int idx_start_pos = name.find("[");
    int idx_end_pos = name.find("]");
    int ret;
    if (idx_start_pos != (int) string::npos && idx_end_pos != (int) string::npos) {
        string index_str = name.substr(idx_start_pos+1, (idx_end_pos-(idx_start_pos+1)));
        istringstream converter(index_str);
        if (!(converter >> idx) && converter.tellg() != (int) index_str.size()) {
            ArgumentType type;
            ret = getType(&type, index_str);
            if (ret != 0 || type != INT) {
                return 1;
            }
            ret = getValue(&idx, index_str);
            if (ret != 0) {
                return ret;
            }
        }
        name = name.substr(0, idx_start_pos);
    } else if (idx_start_pos != (int) string::npos || idx_end_pos != (int) string::npos) {
        return 1;
    }
    if (intArrayMap.find(name) != intArrayMap.end() && type == INT) {
        if (idx >= 0 && idx < (int) intArrayMap[name].size()){
            intArrayMap[name][idx] = *(int*) value;
        } else {
            return 1;
        }
    } else if (doubleArrayMap.find(name) != doubleArrayMap.end() && type == DOUBLE) {
        if (idx >= 0 && idx < (int) doubleArrayMap[name].size()){
            doubleArrayMap[name][idx] = *(double*) value;
        } else {
            return 1;
        }
    } else if (stringArrayMap.find(name) != stringArrayMap.end() && type == STRING) {
        if (idx >= 0 && idx < (int) stringArrayMap[name].size()){
            stringArrayMap[name][idx] = *(string*) value;
        } else {
            return 1;
        }
    } else if (positionArrayMap.find(name) != positionArrayMap.end() && type == POSITION) {
        if (idx >= 0 && idx < (int) positionArrayMap[name].size()){
            positionArrayMap[name][idx] = *(Position*) value;
        } else {
            return 1;
        }
    } else if (type == INT) {
        intMap[name] = *(int*) value;
    } else if (type == DOUBLE) {
         doubleMap[name] = *(double*) value;
    } else if (type == STRING) {
        stringMap[name] = *(string*) value;
    } else if (type == POSITION) {
        positionMap[name] = *(Position*) value;
    } else {
        return 1;
    }
    return 0;
}

int VariableRegister::deleteValue(string name) {
    
    if (isGoodVariableName(name,NORMAL)) // Sanity check
        return 1;

	unsigned long int ret = 0;
    
    ret += intMap.erase(name);
    ret += doubleMap.erase(name);
    ret += stringMap.erase(name);
    ret += positionMap.erase(name);
    ret += intArrayMap.erase(name);
    ret += doubleArrayMap.erase(name);
    ret += stringArrayMap.erase(name);
    ret += positionArrayMap.erase(name);

    if (ret > 0)
			return 0;
	return 1;
}

bool VariableRegister::existsValue(string name) {
    
    return ((intMap.find(name) != intMap.end()) ||
            (doubleMap.find(name) != doubleMap.end()) ||
            (stringMap.find(name) != stringMap.end()) ||
            (positionMap.find(name) != positionMap.end()) ||
            (intArrayMap.find(name) != intArrayMap.end()) ||
            (doubleArrayMap.find(name) != doubleArrayMap.end()) ||
            (stringArrayMap.find(name) != stringArrayMap.end()) ||
            (positionArrayMap.find(name) != positionArrayMap.end()));
    
}

/****************************************************************************/
/* Includes                                                                 */
/****************************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>

#include "../include/Logger.hh"
#include "../include/Connection.hh"
#include "../include/Brain.hh"
#include "../include/Helper.hh"

using namespace std;

/****************************************************************************/
/* Implementation                                                           */
/****************************************************************************/

Logger::Logger (Brain* _brain, Connection* _connection, string logfile_n) {
    
    brain = _brain;
    connection = _connection;
	logfile_name = logfile_n;
    brain->setLogger(this);

	logfile.open(logfile_name.c_str(), ios::out);
    logfile.close();
}

Logger::~Logger() {
}

void Logger::log(pair<string, time_t> logmessage) {

    logfile.open(logfile_name.c_str(), ios::out | ios::app);
    if (!logfile.is_open()) {
        return ;
    }
    this->logfile << ctime(&(logmessage.second)) << " : " << logmessage.first << endl;

    logfile.close();
}

int Logger::sendMessageToBrain(string message) {

    int ret;
    char ch;

    _deep_debug_("%s\n",message.c_str());

    vector<string> vec;
    for(int i=0;(unsigned int)i<message.size();++i)
        if (message[i] == ';')
        {
            vec.push_back( message.substr(0,i+1) );
            message = message.substr(i+1);
            i = 0;
        }

    for(unsigned int i=0;i<vec.size();++i) {
        message = vec[i];
        ch = message[0];
        switch (ch) {
        case 'I':
            ret = brain->initializeMemory(message);
            if (ret != 0) {
                log(make_pair("Cannot initialize memory!\n",time(NULL)));
                return LOGENDROUND;
            }
            break ;
        case 'T':
            ret = brain->parseData(message);
            if (ret != 0) {
                log(make_pair("Fail to parse telemetry data!\n",time(NULL)));
            }
            break;
        case 'B':
            log(make_pair("Rover has hit by Boulder!\n",time(NULL)));
            break;
        case 'E':
            log(make_pair("End Game!\n",time(NULL)));
            ret = brain->cleanup();
            if (ret != 0) {
                log(make_pair("Failure to cleanup!",time(NULL)));
            }
            return LOGENDROUND;
        case 'C':
            log(make_pair("Rover fell in crater!\n",time(NULL)));
            break;
        case 'K':
            log(make_pair("Rover was killed by martian!\n",time(NULL)));
            break;
        case 'S':
            log(make_pair("Rover arrived at base!\n",time(NULL)));
            break;
        default:
            log(make_pair("Bad type of message!\n",time(NULL)));
            break;
        }
    }
	return LOGROVERGOON;
}

int Logger::sendMessageToServer(string message) {
    _deep_debug_("%s\n",message.c_str());
    return this->connection->sendMessageToServer(message);
}

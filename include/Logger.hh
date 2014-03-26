#ifndef _LOGGER_HH
#define _LOGGER_HH

/****************************************************************************/
/* Includes                                                                 */
/****************************************************************************/
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <utility>
#include <cerrno> 
#include "Connection.hh"
#include "Brain.hh"

class Brain;
class Connection;

/****************************************************************************/
/* Prototypes                                                               */
/****************************************************************************/


enum {
    LOGROVERGOON,
    LOGENDROUND
};

/**
 * @class Logger
 * Class Logger keeps the log of all errors (both runtime and complile-time)
 * in the file, supplied.
 */

class Logger{

private:
    // Private members
	std::string logfile_name;    /**< Name of the file, where logs should be kept. */
	std::ofstream logfile;   /**< File stream to write to desired file. */
	Brain* brain;   /**< Instance of Brain to refer to. */
	Connection* connection;     /**< Instance of Connection to exchange messages. */

public:
    // Constructors and destructors
    
    /**
     * @brief Public constructor of the Logger class.
     * @param _brain  Pointer to Brain, that we are referring to.
     * @param logfile  File, where we want to write logs (default: errorlog.txt).
     */
	Logger(Brain* _brain, Connection* _connection, const std::string logfile = "errorlog.txt");
    
    /**
     * @brief Public destructor of the Logger class.
     */
	~Logger();


    /**
     * @brief   Method to write a message to the log.
     * @param   logmessage Pair of message and its timestamp.
     */
	void log(std::pair<std::string, time_t> logmessage);

    /**
     * @brief   Method to send a message to the server.
     * @param   message String with message, that we want to send.
     * @return  If successfully sent, 1, error code otherwise.
     */
	int sendMessageToServer(std::string message);

    /**
     * @brief   Method to send a message to the brain.
     * @param   message String with message, that we want to send.
     * @return  If successfully sent, 1, error code otherwise.
     */
	int sendMessageToBrain(std::string message);
};

#endif // ! _LOGGER_HH

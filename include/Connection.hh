#ifndef _CONNECTION_HH
#define _CONNECTION_HH

/****************************************************************************/
/* Includes                                                                 */
/****************************************************************************/
#include <iostream>
#include <string>
#include "Brain.hh"
#include "Logger.hh"
#include "ClientSocket.hh"

class Brain;
class Logger;

#define MAXNRGAMES 10

/****************************************************************************/
/* Prototypes                                                               */
/****************************************************************************/

/**
 * @class Connection
 * Connection dictates interactions between components of the software,
 * is responsible for establishing and keeping connection to the server and
 * forwarding received data to the right recepients.
 */

class Connection {
    
private:
    // Private members
    ClientSocket *socket; /**< Instance of the socket, that we use to connect. */
    int signal; /**< Status of incoming data (1 - available, 0 - not available) */
    Brain *brain; /**< Instance of the Brain to pass messages to. */
    Logger *logger; /**< Instance of the Logger to pass messages to. */

public:
    // Constructors and destructors
    
	/**
	* @brief Public constructor of the Connection class
	* @param host host address
	* @param port port number
	*/
	Connection(std::string host, int port, std::string brainfile);
    
    /**
     * @brief Public destructor of the Connection class
     */
    ~Connection();
    
    //Public methods
    
    /**
     * @brief   Method to accept a message from the server and forward it appropriately.
     * @return  If successfully done, 1, error code otherwise.
     */
	int acceptMessage();

    /**
     * @brief   Method to send a message to the server.
     * @param   message String with message, that we want to send.
     * @return  If successfully sent, 1, error code otherwise.
     */
	int sendMessageToServer(std::string message);
};

#endif // ! _CONNECTION_HH

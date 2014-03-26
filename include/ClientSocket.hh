#ifndef _CLIENTSOCKET_HH
#define _CLIENTSOCKET_HH

/****************************************************************************/
/* Includes                                                                 */
/****************************************************************************/
#include <iostream>     // Enable console output for debugging purposes.
#include <string>       // Enable strings and functions on them.
#include "Socket.hh"     // Enable generic socket (parent class).

using namespace std;

/****************************************************************************/
/* Prototypes                                                               */
/****************************************************************************/

#define MAXMESSAGELENGTH 2048

/**
 * @class ClientSocket
 * ClientSocket is a child of generic Socket class, that helps us to easily
 * interact with it. Main purposes of the class are establishing connection,
 * sending and receiving messages from the specified host.
 */

class ClientSocket : public Socket {

private:
    // Private members
    string _host;   /**< Host name */
    int _port;      /**< Port number */

public:
    // Constructors and destructors
    
    /**
     * @brief   Public constructor of ClientSocket class.
     * @param   host String with IP address of the host.
     * @param   port  Port number, used by host.
     */
	ClientSocket(string host, int port);

	/**
	* @brief Public destructor of the ClientSocket class.
	*/
	~ClientSocket();

    // Public methods
    
    /**
     * @brief   Method to send a message to the server.
     * @param   msg String containing message that we want to send.
     * @return  If successfully received, 1, error code otherwise.
     */
	int sendclient(string msg);

    /**
     * @brief   Method to receive a message from the server.
     * @param   msg Address in memory to write received message to.
     * @return  If successfully received, 1, error code otherwise.
     */
	int recvclient(string& msg);

	/**
	* @brief Getter method for _host.
	* @return Returns host name.
	*/
    string getHost();

	/**
	* @brief Getter method for _port.
	* @return Returns port number.
	*/
    int getPort();
};

#endif // ! _CLIENTSOCKET_HH

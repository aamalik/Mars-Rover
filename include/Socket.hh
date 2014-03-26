/****************************************************************************/
/* Taken from previous year's winning project                 */
/* Provided by the TAs.                                           */
/****************************************************************************/

#ifndef _SOCKET_HPP
#define _SOCKET_HPP

/****************************************************************************/
/* Includes                                                                 */
/****************************************************************************/

#include <netinet/in.h>                 // Network related types: sockaddr_in
#include <string>                       // STL string

/****************************************************************************/
/* Prototypes                                                               */
/****************************************************************************/

/**
 * @class Socket
 */
class Socket
{
    // Typedefs
    typedef struct sockaddr_in _SockAddr;   /**< Socket address container   */

    // Private members
    int         _fd;                    /**< File Descriptor of the socket  */
    _SockAddr   _outsideAddr;           /**< Outside socket physical address*/
    std::string _host;                  /**< Host name                      */
    int         _port;                  /**< Port number                    */
    bool        _isOpen;                /**< Socket open / closed state     */

    // Constructors and destructors

private:
    /**
     * @brief Private constructor of the OutSocket class.
     */
    Socket();

public:

  /**
     * @brief Public constructor of the OutSocket class.
     */
    Socket(std::string aHost, int aPort);

    /**
     * @brief Public constructor of the OutSocket class.
     */
    Socket(int aPort);

    /**
     * @brief Destructor of the OutSocket class
     */
    ~Socket();

    // Public methods

    /**
     * @brief Method to build an OutSocket by accepting a connection
     *        on a specified socket.
     * @param aFd
     */
    static Socket* buildAcceptedConnection(int aFd);

    /**
     * @brief    Method enable connection to a endpoint address.
     *
     * @return   0 on success, -1 on failure.
     */
    int enable();

    /**
     * @brief   Method to write data to the endpoint of the OutSocket.
     *
     * @param   pAddr   pointer to the address from where to write data
     * @param   nrBytes maximum number of bytes to be written
     * @return  number of bytes written on success
     * @return  -1 on failure
     */
    int write(const void* pAddr, int nrBytes);

    /**
     * @brief   Method to read data from the endpoint of the OutSocket.
     *
     * @param   pAddr   pointer to the address where to place read data
     * @param   nrBytes maximum number of bytes to be read
     * @return  the number of bytes read on success
     * @return  -1 on failure
     */
    int read(void* pAddr, int nrBytes);

    /**
     * @brief Method to set timeout of the socket
     */
    int timeout(int sec);

    /**
     * Getter method for the file descriptor.
     */
    int getFd();
};

#endif

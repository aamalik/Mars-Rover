/**
 * @file Socket.cpp
 * @author Provided by TAs
 */

/****************************************************************************/
/* Includes                                                                 */
/****************************************************************************/

#include <string.h>                     // Mem-related functions: memcpy
#include <sys/socket.h>                 // ISO C Socket library
#include <sys/types.h>                  // Datatypes: size_t, socklen_t
#include <netdb.h>                      // struct hostent, gethostbyname
#include <cerrno>                       // C errno codes
#include <cstdio>                       // C standard I/O
#include "../include/Socket.hh"                // Socket class definition
#include <unistd.h>

/****************************************************************************/
/* Constants                                                                */
/****************************************************************************/

#define  SOCKET_DEFAULT_HOST    "localhost"

/****************************************************************************/
/* Implementation                                                           */
/****************************************************************************/

using namespace std;


Socket::Socket() :
        _isOpen ( false )
{
}


Socket::Socket(string aHost,
                     int    aPort) :
        _host   ( aHost ),
        _port   ( aPort ),
        _isOpen ( false )
{
}


Socket::Socket(int aPort) :
        _host   ( SOCKET_DEFAULT_HOST ),
        _port   ( aPort ),
        _isOpen ( false )
{
}


Socket::~Socket()
{
    if (this->_isOpen)
    {
        int ret;

        ret = close(this->_fd);
        if (ret == -1)
        {
            perror("close:");
        }
    }
}

Socket* Socket::buildAcceptedConnection(int aFd)
{
    Socket* outsock;
    int size;

    size = sizeof(_SockAddr);

    outsock = new Socket();
    outsock->_fd = accept(aFd, (struct sockaddr*)&outsock->_outsideAddr,
                          (socklen_t*)&size);
    if (outsock->_fd < 0) goto fail;

    outsock->_isOpen = true;

    return outsock;

fail:
    delete outsock;
    return NULL;
}


int Socket::enable()
{
    int ret;
    struct hostent *server;

    server = gethostbyname(this->_host.c_str());
    if (server == NULL) goto fail;

    this->_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->_fd == -1)
    {
        perror("socket");
        goto fail;
    }
    else
    {
        this->_isOpen = true;
    }

    this->_outsideAddr.sin_family = AF_INET;
    memcpy(&this->_outsideAddr.sin_addr.s_addr,
           server->h_addr,
           server->h_length);
    this->_outsideAddr.sin_port = htons(this->_port);
    // Open _fd
    ret = connect(this->_fd,
                  (sockaddr*) &this->_outsideAddr, sizeof(this->_outsideAddr));
    if (ret == -1) goto fail;

    return 0;
fail:
    if (this->_isOpen) close(this->_fd);
    return -1;
}



int Socket::write(const void* pAddr, int nrBytes)
{
    int ret;
    int len;

    if (!this->_isOpen) goto fail;

    ret = 1; // dummy positive value
    len = 0;
    while (len < nrBytes && ret > 0)
    {
        ret = ::write(this->_fd, (const char*)pAddr + len, nrBytes - len);
        len += ret;
    }
    if (ret == -1) goto fail;

    return len;

fail:
    return -1;
}

int Socket::timeout(int sec) {

    timeval tv;
    fd_set fdset;

    tv.tv_sec = (time_t)sec;;
    tv.tv_usec = 0;
    FD_ZERO(&fdset);
    FD_SET(_fd,&fdset);

    int ret = select(_fd + 1, &fdset, NULL, NULL, &tv);
    if (ret == 0)
        return 1;
    return 0;
}


int Socket::read(void* pAddr, int nrBytes)
{
    int ret;

    if (!this->_isOpen) goto fail;

    ret = 1; // dummy positive value
    ret = ::read(this->_fd, (char*)pAddr, nrBytes);

    if (ret == -1) goto fail;
    ((char*)pAddr)[ret] = '\0';

    return ret;

fail:
    return -1;
}

int Socket::getFd() {
    return _fd;
}

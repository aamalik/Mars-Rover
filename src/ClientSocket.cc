/****************************************************************************/
/* Includes                                                                 */
/****************************************************************************/
#include "../include/ClientSocket.hh"

/****************************************************************************/
/* Implementation                                                           */
/****************************************************************************/

ClientSocket::ClientSocket(string host, int port) : Socket(host,port){
	
    // Properties indroduced by XP1 people. Useless, but we can't do anything about it.
    _host = host;
	_port = port;
}

ClientSocket::~ClientSocket() {

}

int ClientSocket::sendclient(string msg) {
    unsigned int ret = Socket::write((const void*)msg.c_str(),msg.length()*sizeof(char));

    if (ret != msg.length()) 
        return 1;
    return 0;
}

int ClientSocket::recvclient(string& msg) {

    char message[MAXMESSAGELENGTH];

    int ret = Socket::read((void*) message, MAXMESSAGELENGTH);
    if (ret == -1) {
        return ret;
    }

    msg = (string)message;
    return 0;
}

string ClientSocket::getHost() {
    return _host;
}

int ClientSocket::getPort() {
    return _port;
}

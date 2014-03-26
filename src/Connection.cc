/****************************************************************************/
/* Includes                                                                 */
/****************************************************************************/
#include <time.h>
#include <iostream>
#include <string>

#include "../include/Helper.hh"
#include "../include/Connection.hh"
#include "../include/Logger.hh"
#include "../include/Brain.hh"
#include "../include/Parser.hh"

using namespace std;

/****************************************************************************/
/* Implementation                                                           */
/****************************************************************************/

Connection::Connection(string host, int port, string brainfile) {

    Brain* brainptr = NULL;
    int ret;

    brain = NULL;
    logger = NULL;
    socket = NULL;

    if ((ret = Parser::parseFile(&brainptr,brainfile,0)) != 0) {
        cerr << "Cannot open Brain!" << endl;
        return ;
    }
    if (brainptr == NULL) {
        cerr << "Brain not initialized!" << endl;
        return ;
    }

    this->brain = brainptr;

    this->logger = new Logger(brain,this);

	this->socket = new ClientSocket(host, port);
}

Connection::~Connection() {
    //Added to prevent memory leaks by XP2.
    if (brain != NULL) 
        delete brain;
    if (socket != NULL)
        delete socket ;
    if (logger != NULL)
        delete logger ;
}

int Connection::acceptMessage() {
    
    string buffer;
    int ok,ret;

    if (socket == NULL) 
        return 1;
    if (brain == NULL)
        return 1;
    if (logger == NULL)
        return 1;
 
    _debug_("Connection: Starting Thread\n");
    ret = brain->startThread();
    if (ret != 0) {
        cerr << "Cannot start Thread!" << endl;
        return 1;
    }

    _debug_("Connection: Establishing Connection!\n");
    ret = socket->enable();
    if (ret != 0) {
        cerr << "Cannot establish connection!" << endl;
        return 1;
    }

    /* Make timeout value for socket! */

    for(int i=0; i < MAXNRGAMES; ++i) {

        ret = socket->timeout(3);
        if (ret != 0) {
            return 0;
        }

        _debug_("Connection: Start Game\n");
        ok = 1;
        while (ok) {
            ret = socket->recvclient(buffer);
            if (ret != 0) {
                logger->log(make_pair("Connection error: Cannot receive message from server!\n",time(NULL)));
                continue;
            }

            ret = logger->sendMessageToBrain(buffer);
            if (ret == LOGENDROUND) {
                _debug_("Connection: End Game\n");
                ok = 0;
            }
        }
    }

    return 0;
}

int Connection::sendMessageToServer(string message) {
    int ret = this->socket->sendclient(message);
    if (ret != 0) {
        logger->log(make_pair("Connection error: Cannot send message '" + message + "' to server!\n",time(NULL)));
        return 1;
    }
    return 0;
}

/****************************************************************************/
/* Includes                                                                 */
/****************************************************************************/

#include <pthread.h>
#include <iostream>
#include <string>
#include <time.h>
#include <typeinfo>
#include <unistd.h>

#include "../include/Brain.hh"                	// Brain class definition
#include "../include/MemoryHandler.hh"
#include "../include/Connection.hh"
#include "../include/Logger.hh"
#include "../include/InstructionIF.hh"
#include "../include/Helper.hh"

using namespace std;

/****************************************************************************/
/* Implementation                                                           */
/****************************************************************************/

Brain::Brain(vector<InstructionIF*> _instructions) {
	this->instructionPointer = 0;
	this->instructionBreakPointer = -1;
	this->instructionErrorBreakPointer = 1;
    this->instructions = _instructions;
    
	this->memoryHandler = new MemoryHandler();
    logger = NULL;
    signal = 0;

    signalStart = new pthread_mutex_t;
    signalMemory = new pthread_mutex_t;
    if (pthread_mutex_init(signalStart,NULL) ) {
        printf("Brain: Cannot initialize mutex!\n");
        signalStart = NULL;
    }
    if (pthread_mutex_init(signalMemory,NULL) ) {
        printf("Brain: Cannot initialize mutex!\n");
        signalStart = NULL;
    }

    thread = 0;
}

Brain::~Brain() {
    int ret;

    if (signalStart == NULL)
        return ;
    if (signalMemory == NULL)
        return ;

    pthread_mutex_lock(signalMemory);
    pthread_mutex_trylock(signalStart);
    pthread_mutex_unlock(signalStart);
    signal = ENDGAME;
    pthread_mutex_unlock(signalMemory);

    if (thread != 0) {
        ret = pthread_join(thread,NULL);
        if (ret != 0) {
            cerr << "Cannot join Thread 2!" << endl;
        }
    }

    pthread_mutex_destroy(signalMemory);
    pthread_mutex_destroy(signalStart);
    delete signalMemory;
    delete signalStart;

    for(unsigned int i=0;i<instructions.size();++i) {
        delete instructions[i];
    }

    delete memoryHandler;

    instructions.clear();
}

int Brain::initializeMemory(string message) {

    signal = EVERYTHINGISFINE;
    return this->memoryHandler->init(message);
}

int Brain::parseData(string message) {
    int ret;

    pthread_mutex_lock(signalMemory);
    ret = memoryHandler->parseData(message);
    if (ret != 0) {
        pthread_mutex_unlock(signalMemory);
        return 1;
    }
    if (signal != ROVERWAITFORDATA)
        signal = ROVERGOTDATABREAK;
    signal = ROVERGOTDATA;
    pthread_mutex_trylock(signalStart);
    pthread_mutex_unlock(signalStart);
    pthread_mutex_unlock(signalMemory);

    return 0;
}

int Brain::cleanup() {

    pthread_mutex_lock(signalMemory);

    pthread_mutex_trylock(signalStart);
    pthread_mutex_unlock(signalStart);

    signal = ROVERDIED;
    int ret = memoryHandler->clean();

    pthread_mutex_unlock(signalMemory);

    return ret;
}

int Brain::startThread() {

    int ret;

    if (logger == NULL) {
        cerr << "Brain: Logger undefined" << endl;
        return 1;
    }

    if (signalStart == NULL) {
        cerr << "Brain: Mutex uninitialized!" << endl;
        return 1;
    }

    if (signalMemory == NULL) {
        cerr << "Brain: Mutex uninitialized!" << endl;
        return 1;
    }

    pthread_mutex_lock(signalStart);

    ret = pthread_create(&thread, NULL, Brain::execute, this);
    if (ret != 0) {
        cerr << "Brain: Cannot create second thread!" << endl;
        return 1;
    }
    
    return 0;
}


void* Brain::execute(void* args) {
    int lastInstructionPointer;
    int ret;
    Brain* b = (Brain*)args;

    int run = 1,alive;
    while (run) {
        pthread_mutex_lock(b->signalStart);
        b->instructionPointer = 0;

        if (b->signal == ENDGAME) {
            return NULL;
        }

        alive = 1;
        while (alive) {
            pthread_mutex_lock(b->signalMemory);

            if (b->signal == ENDGAME)
                return NULL;

            if (b->signal == ROVERDIED) {
                alive = 0;
                pthread_mutex_unlock(b->signalMemory);
                break;
            }
            if (b->signal == ROVERWAITFORDATA) {
                pthread_mutex_unlock(b->signalMemory);
                pthread_mutex_lock(b->signalStart);
                continue;
            }
            if (b->signal == ROVERGOTDATABREAK) {
                if (b->instructionBreakPointer != -1) {
                    b->instructionPointer = b->instructionBreakPointer + 1;
                }
            }

            if ((unsigned int)b->instructionPointer >= b->instructions.size()) {
                b->logger->log( make_pair("Instruction Pointer out of scope!", time(NULL)) );
                if (b->instructionErrorBreakPointer != -1) {
                    b->instructionPointer = b->instructionErrorBreakPointer + 1;
                } else {
                    b->instructionPointer = 0;
                }
            }

            if (b->instructionPointer  == 11 || 
                b->instructionPointer  == 4 || 
                b->instructionPointer  == 5 ) {
                double x;
                b->memoryHandler->getValue(&x,"ang");
                _deep_debug_("Ang = %f\n",x);
            }

            _deep_debug_("Brain: execute: %s at %d\n",typeid(*b->instructions[b->instructionPointer]).name(), b->instructionPointer+1 );
            lastInstructionPointer = b->instructionPointer;
            ret = b->instructions[ b->instructionPointer ]->execute(
                b->memoryHandler,&b->instructionPointer);
            if (b->instructionPointer == lastInstructionPointer) {
                b->instructionPointer ++;
            }

            if (ret != ICONTINUE) {
                if (ret == IMEMERROR) {
                    b->logger->log( make_pair("Brain: Memory Error!",time(NULL)) );
                    if (b->instructionErrorBreakPointer != -1) {
                        b->instructionPointer = b->instructionErrorBreakPointer;
                    }
                } else if (ret == IRETURN) {
                    b->logger->sendMessageToServer( b->memoryHandler->getReturnString() );
                } else if (ret == IWAIT) {
                    b->signal = ROVERWAITFORDATA;
                } 
            }

            pthread_mutex_unlock( b->signalMemory );
        }
    }
    return NULL;
}

void Brain::setInstructionBreakPointer(int value) {
    if ((unsigned int) value < instructions.size() )
        instructionBreakPointer = value;
}

void Brain::setInstructionErrorBreakPointer(int value) {
    if ((unsigned int) value < instructions.size() )
        instructionErrorBreakPointer = value;
}

void Brain::setLogger(Logger* aLogger) {
    logger = aLogger;
}
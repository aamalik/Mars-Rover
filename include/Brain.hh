#ifndef _BRAIN_HH
#define _BRAIN_HH

/****************************************************************************/
/* Includes                                                                 */
/****************************************************************************/
#include <iostream>         // Enable console output for debugging purposes.
#include <vector>           // Enable vectors and operations on them.
#include <sstream>          // Enable reading from string stream
#include <cstring>          // Enable working with C-style strings
#include <pthread.h>        // Enable threading
#include <string>           // Enable working with strings
#include <time.h>           // Enable working with time
#include "Logger.hh"         // Enable logger to be used in the implementation.
#include "MemoryHandler.hh"  // Enable MemoryHandler interaction
#include "InstructionIF.hh"  // Enable InstructionIF methods
#include "Connection.hh"    // Enable references to Connection class


class MemoryHandler;
class Logger;
class Connection;
class InstructionIF;

/****************************************************************************/
/* Prototypes                                                               */
/****************************************************************************/


enum SIGNALTYPE {
    EVERYTHINGISFINE,
    ROVERGOTDATA,
    ROVERGOTDATABREAK,
    ROVERWAITFORDATA,
    ROVERDIED,
    ENDGAME
};

/**
 * @class Brain
 * Brain is responsible for all the logic behind rover's moving. First, Parser
 * initializes this class with a parsed brain file and after that, this class
 * will take over in all decision making of the algorithm.
 */

class Brain {

private:
    // Private members
    int instructionPointer; /**< Position of instruction being executed. */
    Logger* logger; /**< Instance of Logger to write to logs and interact with Connection. */
    MemoryHandler* memoryHandler; /**< Used to initialize and keep track of memory. */
    std::vector< InstructionIF* > instructions; /**< Used to hold instructions in */

    int signal; /**< Indication of incoming telemetry data to manipulate threads. */
    int instructionBreakPointer; /**< Will be set if some instructions need to be re-executed after updating telemetry. */
    int instructionErrorBreakPointer; /**< Will be set if error occured during running. */

    pthread_t thread;
    pthread_mutex_t *signalMemory,*signalStart;    
   
private:
    //Private methods
    
    /**
     * @brief   Private method, that Brain uses to do logical computations of instructions, that are present.
     */
    static void* execute(void* arg);

public:
    // Public constructors and destructors
    
    /**
     * @brief   Constructor for Brain class
     * @param  instructions  Vector of Instructions to be exectuted
     */
    Brain(std::vector< InstructionIF* > instructions);
    
    /**
     * @brief   Destructor for Brain class
     */
    ~Brain();
    
    //Public methods
    
    /**
     * @brief   Method to initialize memory in MemoryHandler with a given string.
     * @param   message String that will be sent.
     * @return  If successfully done, 0, error code otherwise.
     */
    int initializeMemory(std::string message);
    
    /**
     * @brief   Method to start thread that will constantly be responsible for executing instructions.
     * @return  If successfully done, 0 s, error code otherwise.
     */
    int startThread();
    
    /**
     * @brief   Method to parse data received from server through Logger class, so Brain understands it.
     * @param   message String to be parsed.
     * @return  If successfully done, 1, error code otherwise.
     */
    int parseData(std::string message);

    /**
     * @brief   Brain cleanup
     * @return  0 on success, 1 otherwise
     */
     int cleanup();

     /**
      * @brief Set up the Instruction break pointer value
      * @param value the IBreakPointer value to be set
      */
     void setInstructionBreakPointer(int value);

     /**
      * @brief Set up the Instruction error break pointer value
      * @param value the IErrorBreakPointer value to be set
      */
     void setInstructionErrorBreakPointer(int value);
    
    /**
     * @brief Method to set the logger
     * @param aLogger the pointer to the logger to be set
     */ 
     void setLogger(Logger *aLogger);
};


#endif // ! _BRAIN_HH

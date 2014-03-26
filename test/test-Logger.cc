#include <iostream>
#include <vector>

#include "test-Logger.h"
#include "Brain.hh"
#include "Logger.hh"
#include "InstructionIF.hh"
#include "ArgumentType.hh"
#include "Connection.hh"


CPPUNIT_TEST_SUITE_REGISTRATION(LoggerTest);

void LoggerTest::setUp(){

	Connection c("localhost",17676,"brainfile");
	vector<InstructionIF*> vec;
	Brain b(vec);

	l = new Logger(&b,&c,"errorlog.txt");

}

void LoggerTest::tearDown(){
	delete l;
}

void LoggerTest::testSendMessageToBrain(){

	// If you are wondering why it returns LOGROVERGOON even if it is a bad message:
	// The answer is that the logger doesnt end the round if someone sends it a bad 
	// telemetry data. It doesn't need to inform the Connection class about it.
	// Only if we have a bad init message or end message we return end round message 
	// to connection

	string msg;

	msg = "I 100 100 (bad message);";
	CPPUNIT_ASSERT(LOGENDROUND == l->sendMessageToBrain(msg));

	msg = "T something something 100 100;";
	CPPUNIT_ASSERT(LOGROVERGOON == l->sendMessageToBrain(msg));

	msg = "E 100 100;";
	//CPPUNIT_ASSERT(LOGENDROUND == l->sendMessageToBrain(msg));

	msg = "S 199 199;E 100 100;";
	//CPPUNIT_ASSERT(LOGENDROUND == l->sendMessageToBrain(msg));
}

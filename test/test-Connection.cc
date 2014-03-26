#include <iostream>
#include <vector>

#include "test-Connection.h"
#include "Brain.hh"
#include "Connection.hh"
#include "InstructionIF.hh"
#include "ArgumentType.hh"


CPPUNIT_TEST_SUITE_REGISTRATION(ConnectionTest);

void ConnectionTest::setUp(){

	c1 = new Connection("localhost",17676,BRAINFILE);
	c2 = new Connection("nothing",17676,BRAINFILE);
	c3 = new Connection("localhost",0,BRAINFILE);
	c4 = new Connection("localhost",17676,"nobrain");
}

void ConnectionTest::tearDown(){
	delete c1;
	delete c2;
	delete c3;
	delete c4;
}

void ConnectionTest::testAcceptConnection(){

	// TO make this work you have to start up the server and 
	// .. and make sure the brain file still exists
	CPPUNIT_ASSERT(c1->acceptMessage());


	// Bad input
	CPPUNIT_ASSERT(c2->acceptMessage());
	CPPUNIT_ASSERT(c3->acceptMessage());
	CPPUNIT_ASSERT(c4->acceptMessage());
}

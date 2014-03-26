#include "test-Socket.h"

CPPUNIT_TEST_SUITE_REGISTRATION( SocketTest );

void SocketTest::setUp()
{
	s = new Socket("localhost",17676);
}

void SocketTest::tearDown()
{
	delete s;
}

void SocketTest::testEnable() {

	// Start the server on port 17676 on localhost

	// Check
	// CPPUNIT_ASSERT( !s->enable() ); 
}

void SocketTest::testReceive() {

	// Start the server on port 17676 on localhost

	// And check
	//CPPUNIT_ASSERT( !s->enable() );

}

void SocketTest::testSendFunc() {

	// Start the server on port 17676 on localhost

	// And check
	//CPPUNIT_ASSERT( !s->enable() );
}
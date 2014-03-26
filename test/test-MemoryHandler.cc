#include "test-MemoryHandler.h"
#include "ArgumentType.hh"

CPPUNIT_TEST_SUITE_REGISTRATION( MemoryHandlerTest );

void MemoryHandlerTest::setUp()
{
	mh1 = new MemoryHandler();
}

void MemoryHandlerTest::tearDown()
{
	delete mh1;
}

void MemoryHandlerTest::testConstructor() {
  // Set up
  int *time, ret;
  int time2;
  time = &time2;

  // Process
  ret = mh1->getValue((void *)time, "CurrentTime");

  // Check
  CPPUNIT_ASSERT_EQUAL( 0, ret );
  CPPUNIT_ASSERT_EQUAL( 0, *time );
}

void MemoryHandlerTest::testInit() {
	int ret;
	//good init string
	std::string data1 = "I 100.00 101.000 1000.000 1.000 2.000 3.000 4.000 5.000;";
	//bad init strings
	std::string data2 = "I 100.00 101.000 1000.000 1.000 2.000 3.000 4.000 5.000"; // missing semicolon
	std::string data3 = "I 100.00 101.000 1000.000 1.000 2.000 3.000 4.000;"; //too few arguments
	std::string data4 = "I 100.00 101.000 1000.000 1.000 2.000 3.000 4.000 5.000 6.000;"; //too many arguments

	ret = mh1->init(data1);
	CPPUNIT_ASSERT_EQUAL(0, ret);
	
	ret = mh1->init(data2); 
	CPPUNIT_ASSERT(ret != 0);
	ret = mh1->init(data3); 
	CPPUNIT_ASSERT(ret != 0);
	ret = mh1->init(data4); 
	CPPUNIT_ASSERT(ret != 0);
}

void MemoryHandlerTest::testParseData() {
	int ret;
	double x; int s;
	//Set up
	std::string data1 = "T 100 aL 2.000 3.000 4.000 5.000 b 6.000 7.000 8.000;";
	std::string data2 = "T 1000 -- 112.000 113.000 114.000 115.000 b 6.000 7.000 8.000 m 9.000 8.000 10.000 11.000 c 12.000 13.000 14.000;";
	//bad telemetry data:
	std::string data3 = "T 100 br 2.000 3.000 4.000 5.000 b 6.000 7.000 8.000"; //missing semicolon
	std::string data4 = "T 100 -- 2.000 3.000 4.000 5.000 b 6.000 7.000 8.000 9.000;"; //too many object parameters
	std::string data5 = "T 100 -L 2.000 3.000 4.000 5.000 k 6.000 7.000 8.000;"; //wrong object identifier
	std::string data6 = "T 100 -t 2.000 3.000 4.000 5.000 b 6.000 7.000 8.000;"; //invalid state
	std::string data7 = "T 100 t 2.000 3.000 4.000 5.000 b 6.000 7.000 8.000;"; //invalid state
	std::string data8 = "T 100 t- 2.000 3.000 4.000 5.000 b 6.000 7.000 8.000;"; //invalid state
	std::string data9 = "K 100 a- 2.000 3.000 4.000 5.000 b 6.000 7.000 8.000;";  //wrong message type

	//test forwarding the initialization message:
	std::string initData = "I 100.00 101.000 1000.000 1.000 2.000 3.000 4.000 5.000;";
	int time;

	//Process
	ret = mh1->parseData(data1); 
	CPPUNIT_ASSERT_EQUAL(0, ret);
	ret = mh1->getValue(&time, "CurrentTime");
	CPPUNIT_ASSERT_EQUAL(100, time);
	ret = mh1->getValue(&s, "Rover.TurningState");
	CPPUNIT_ASSERT_EQUAL(1, s);
	ret = mh1->getValue(&x, "Rover.Heading");
	CPPUNIT_ASSERT_EQUAL(4.0, x );
	ret = mh1->getValue(&x, "Boulder[0].X");
	CPPUNIT_ASSERT_EQUAL(6.0, x);

	ret = mh1->parseData(data2); 
	CPPUNIT_ASSERT_EQUAL(0, ret);
	ret = mh1->getValue(&time, "CurrentTime");
	CPPUNIT_ASSERT_EQUAL(1000, time);

	//bad telemetry data:
	ret = mh1->parseData(data3); 
	CPPUNIT_ASSERT(ret != 0);
	ret = mh1->parseData(data4); 
	CPPUNIT_ASSERT(ret != 0);
	ret = mh1->parseData(data5); 
	CPPUNIT_ASSERT(ret != 0);
	ret = mh1->parseData(data6); 
	CPPUNIT_ASSERT(ret != 0);
	ret = mh1->parseData(data7); 
	CPPUNIT_ASSERT(ret != 0);
	ret = mh1->parseData(data8); 
	CPPUNIT_ASSERT(ret != 0);
	ret = mh1->parseData(data9); 
	CPPUNIT_ASSERT(ret != 0);

	ret = mh1->parseData(initData); 
	CPPUNIT_ASSERT_EQUAL(0, ret);
}

void MemoryHandlerTest::testGetType() {
	ArgumentType type;
	int ret;

	ret = mh1->getType(&type, "CurrentTime");

	CPPUNIT_ASSERT_EQUAL(0, ret);
	CPPUNIT_ASSERT_EQUAL(INT, type);
}

void MemoryHandlerTest::testDeleteValue() {
	int ret;
	ret = mh1->deleteValue("CurrentTime");
	CPPUNIT_ASSERT(ret != 0);
}

void MemoryHandlerTest::testSetValue() {
	int ret, value = 1;
	ret = mh1->setValue(&value, INT, "CurrentTime");
	CPPUNIT_ASSERT(ret != 0);
}
#include "test-MapRegister.h"
#include "ArgumentType.hh"

CPPUNIT_TEST_SUITE_REGISTRATION( MapRegisterTest );

void MapRegisterTest::setUp()
{
	mr1 = new MapRegister();
}

void MapRegisterTest::tearDown()
{
	delete mr1;
}

void MapRegisterTest::testParseMapDetails() {
	int ret;
	//good init string
	std::string data1 = "100.00 101.000 1000.000";
	std::string data2 = "-100.00 -101.000 2000.000";
	std::string data3 = "0.000 0.000 1.000";

	//bad init strings
	std::string data4 = "100.00 101.000"; //too few
	std::string data5 = "100.00 aL 1000.000"; //stray letters
	std::string data6 = "100.00 101.000 -1000.000"; //negative time limit


	ret = mr1->parseMapDetails(data1);
	CPPUNIT_ASSERT_EQUAL(0, ret);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(100, mr1->width, 0.0001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(101, mr1->length, 0.0001);
	CPPUNIT_ASSERT_EQUAL(1000, mr1->timeLimit);
	ret = mr1->parseMapDetails(data2);
	CPPUNIT_ASSERT_EQUAL(0, ret);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(-100, mr1->width, 0.0001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(-101, mr1->length, 0.0001);
	CPPUNIT_ASSERT_EQUAL(2000, mr1->timeLimit);
	ret = mr1->parseMapDetails(data3);
	CPPUNIT_ASSERT_EQUAL(0, ret);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, mr1->width, 0.0001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, mr1->length, 0.0001);
	CPPUNIT_ASSERT_EQUAL(1, mr1->timeLimit);
	
	ret = mr1->parseMapDetails(data4); 
	CPPUNIT_ASSERT(ret != 0);
	ret = mr1->parseMapDetails(data5); 
	CPPUNIT_ASSERT(ret != 0);
	ret = mr1->parseMapDetails(data6); 
	CPPUNIT_ASSERT(ret != 0);
}

void MapRegisterTest::testGetType() {
    ArgumentType type;
    int ret;

    ret = mr1->getType(&type, "Map.Homebase.Position");
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_EQUAL(POSITION, type);

    ret = mr1->getType(&type, "Map.Homebase.Speed");
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_EQUAL(DOUBLE, type);

    ret = mr1->getType(&type, "Map.Homebase.Radius");
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_EQUAL(DOUBLE, type);

    ret = mr1->getType(&type, "Map.Homebase.Heading");
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_EQUAL(DOUBLE, type);

    ret = mr1->getType(&type, "Map.Homebase.X");
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_EQUAL(DOUBLE, type);

    ret = mr1->getType(&type, "Map.Homebase.Y");
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_EQUAL(DOUBLE, type);

    ret = mr1->getType(&type, "Map.TimeLimit");
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_EQUAL(INT, type);

    ret = mr1->getType(&type, "Map.Length");
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_EQUAL(DOUBLE, type);

    ret = mr1->getType(&type, "Map.Width");
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_EQUAL(DOUBLE, type);

    ret = mr1->getType(&type, "Map.Drag");
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_EQUAL(DOUBLE, type);
  }

  void MapRegisterTest::testGetValue() {
    int ret;
    SpaceObject so(0, 0, 0, 0, 0), hb(0, 0, 5, 0, 0);
    double length, width, drag;
    int limit;
  	ret = mr1->getValue(&length, "Map.Length");
  	CPPUNIT_ASSERT_EQUAL(0, ret);
  	ret = mr1->getValue(&width, "Map.Width");
  	CPPUNIT_ASSERT_EQUAL(0, ret);
  	ret = mr1->getValue(&drag, "Map.Drag");
  	CPPUNIT_ASSERT_EQUAL(0, ret);
  	ret = mr1->getValue(&limit, "Map.TimeLimit");
  	CPPUNIT_ASSERT_EQUAL(0, ret);
  	//mr1.getValue(&so, "Map.Homebase");

  	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, length, 0.0001);
  	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, width, 0.0001);
  	CPPUNIT_ASSERT_DOUBLES_EQUAL(-1, drag, 0.0001);
  	CPPUNIT_ASSERT_EQUAL(0, limit);

  	//now test parsing different map data and getting it:
  	//(this also tests the very simple and trivial constructor)
  	MapRegister test;
  	test.parseMapDetails("1.000 2.000 3.000"); //set up

  	ret = test.getValue(&length, "Map.Length");
  	CPPUNIT_ASSERT_EQUAL(0, ret);
  	ret = test.getValue(&width, "Map.Width");
  	CPPUNIT_ASSERT_EQUAL(0, ret);
  	ret = test.getValue(&limit, "Map.TimeLimit");
  	CPPUNIT_ASSERT_EQUAL(0, ret);

  	CPPUNIT_ASSERT_DOUBLES_EQUAL(2, length, 0.0001);
  	CPPUNIT_ASSERT_DOUBLES_EQUAL(1, width, 0.0001);
  	CPPUNIT_ASSERT_EQUAL(3, limit);
  }

void MapRegisterTest::testSetValue() {
	int ret;
	MapRegister test;
	double length = 2.5, width = 3.5, drag = 4.5;
	int limit = 200;

	ret = test.setValue(&length, DOUBLE, "Map.Length");
  	CPPUNIT_ASSERT_EQUAL(0, ret);
  	CPPUNIT_ASSERT_DOUBLES_EQUAL(length, test.length, 0.0001);

  	ret = test.setValue(&width, DOUBLE, "Map.Width");
  	CPPUNIT_ASSERT_EQUAL(0, ret);
  	CPPUNIT_ASSERT_DOUBLES_EQUAL(width, test.width, 0.0001);

  	ret = test.setValue(&drag, DOUBLE, "Map.Drag");
  	CPPUNIT_ASSERT_EQUAL(0, ret);
  	CPPUNIT_ASSERT_DOUBLES_EQUAL(drag, test.drag, 0.0001);

  	ret = test.setValue(&limit, INT, "Map.TimeLimit");
  	CPPUNIT_ASSERT_EQUAL(0, ret);
  	CPPUNIT_ASSERT_EQUAL(limit, test.timeLimit);

  	//second set of (negative) values
  	length = -2.5, width = -3.5, drag = -4.5;
	limit = -200;

	ret = test.setValue(&length, DOUBLE, "Map.Length");
  	CPPUNIT_ASSERT_EQUAL(0, ret);
  	CPPUNIT_ASSERT_DOUBLES_EQUAL(length, test.length, 0.0001);

  	ret = test.setValue(&width, DOUBLE, "Map.Width");
  	CPPUNIT_ASSERT_EQUAL(0, ret);
  	CPPUNIT_ASSERT_DOUBLES_EQUAL(width, test.width, 0.0001);

  	ret = test.setValue(&drag, DOUBLE, "Map.Drag");
  	CPPUNIT_ASSERT_EQUAL(0, ret);
  	CPPUNIT_ASSERT_DOUBLES_EQUAL(drag, test.drag, 0.0001);

  	ret = test.setValue(&limit, INT, "Map.TimeLimit");
  	CPPUNIT_ASSERT(ret != 0);
}
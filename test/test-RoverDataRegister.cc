#include "test-RoverDataRegister.h"
#include "ArgumentType.hh"

CPPUNIT_TEST_SUITE_REGISTRATION( RoverDataRegisterTest );

void RoverDataRegisterTest::setUp()
{
	mr1 = new RoverDataRegister();
}

void RoverDataRegisterTest::tearDown()
{
	delete mr1;
}

void RoverDataRegisterTest::testParseRover() {
  int ret;
  //Set up
  std::string data1 = "aL 2.000 3.000 4.000 5.000";
  std::string data2 = "-R -112.500 113.020 -114.000 115.600";
  std::string data3 = "-- 112.000 -113.000 114.000 -115.000";
  std::string data4 = "br -112.000 -113.000 -114.000 -115.000";
  std::string data5 = "bl 0.000 0.000 0.000 0.000";
  //bad telemetry data:
  std::string data6 = "bl 2.000 3.000 4.000"; //too few rover arguments
  std::string data7 = "ax 2.000 3.000 4.000 5.000"; //invalid state
  std::string data8 = "a 2.000 3.000 4.000 5.000"; //invalid state
  std::string data9 = "xx 2.000 3.000 4.000 5.000"; //invalid state
  std::string data10 = "1.000 aL 3.000 4.000 5.000"; //state at wrong point
  std::string data11 = "1.000 3.000 4.000 5.000 bR"; //state at wrong point

  //test for data1
  ret = mr1->parseRover(data1);
  CPPUNIT_ASSERT_EQUAL(0, ret);
  CPPUNIT_ASSERT_EQUAL(3, mr1->speedState);
  CPPUNIT_ASSERT_EQUAL(1, mr1->turningState);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(2, mr1->pos.getX(), 0.0001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(3, mr1->pos.getY(), 0.0001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(4, mr1->heading, 0.0001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(5, mr1->speed, 0.0001);
  //test for data2
  ret = mr1->parseRover(data2);
  CPPUNIT_ASSERT_EQUAL(0, ret);
  CPPUNIT_ASSERT_EQUAL(2, mr1->speedState);
  CPPUNIT_ASSERT_EQUAL(5, mr1->turningState);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(-112.5, mr1->pos.getX(), 0.0001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(113.02, mr1->pos.getY(), 0.0001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(-114, mr1->heading, 0.0001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(115.6, mr1->speed, 0.0001);
  //test for data3
  ret = mr1->parseRover(data3);
  CPPUNIT_ASSERT_EQUAL(0, ret);
  CPPUNIT_ASSERT_EQUAL(2, mr1->speedState);
  CPPUNIT_ASSERT_EQUAL(3, mr1->turningState);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(112, mr1->pos.getX(), 0.0001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(-113, mr1->pos.getY(), 0.0001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(114, mr1->heading, 0.0001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(-115, mr1->speed, 0.0001);
  //test for data4
  ret = mr1->parseRover(data4);
  CPPUNIT_ASSERT_EQUAL(0, ret);
  CPPUNIT_ASSERT_EQUAL(1, mr1->speedState);
  CPPUNIT_ASSERT_EQUAL(4, mr1->turningState);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(-112, mr1->pos.getX(), 0.0001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(-113, mr1->pos.getY(), 0.0001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(-114, mr1->heading, 0.0001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(-115, mr1->speed, 0.0001);
  //test for data5
  ret = mr1->parseRover(data5);
  CPPUNIT_ASSERT_EQUAL(0, ret);
  CPPUNIT_ASSERT_EQUAL(1, mr1->speedState);
  CPPUNIT_ASSERT_EQUAL(2, mr1->turningState);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0, mr1->pos.getX(), 0.0001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0, mr1->pos.getY(), 0.0001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0, mr1->heading, 0.0001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0, mr1->speed, 0.0001);
  
  ret = mr1->parseRover(data6); 
  CPPUNIT_ASSERT(ret != 0);
  ret = mr1->parseRover(data7); 
  CPPUNIT_ASSERT(ret != 0);
  ret = mr1->parseRover(data8); 
  CPPUNIT_ASSERT(ret != 0);
  ret = mr1->parseRover(data9); 
  CPPUNIT_ASSERT(ret != 0);
  ret = mr1->parseRover(data10); 
  CPPUNIT_ASSERT(ret != 0);
  ret = mr1->parseRover(data11); 
  CPPUNIT_ASSERT(ret != 0);
}

void RoverDataRegisterTest::testInit() {
	int ret;
	//good init string
  std::string data1 = "1.000 2.000 3.000 4.000 5.000;";
  std::string data2 = "-1.000 -2.000 -3.000 -4.000 -5.000;";
  std::string data3 = "0.000 0.000 0.000 0.000 0.000;";
  //bad init strings
  std::string data4 = "-1.000 -2.000 -3.000 -4.000 -5.000"; //missing semicolon
  std::string data5 = "1.000 2.000 3.000 4.000;"; //too few arguments
  std::string data6 = "1.000 2.000 3.000 4.000 5.000 6.000;"; //too many arguments


	//test for data1
  ret = mr1->init(data1);
  CPPUNIT_ASSERT_EQUAL(0, ret);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(1, mr1->minSensor, 0.0001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(2, mr1->maxSensor, 0.0001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(3, mr1->maxSpeed, 0.0001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(4, mr1->maxTurn, 0.0001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(5, mr1->maxHardTurn, 0.0001);

  //test for data2
  ret = mr1->init(data2);
  CPPUNIT_ASSERT_EQUAL(0, ret);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(-1, mr1->minSensor, 0.0001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(-2, mr1->maxSensor, 0.0001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(-3, mr1->maxSpeed, 0.0001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(-4, mr1->maxTurn, 0.0001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(-5, mr1->maxHardTurn, 0.0001);

  //test for data3
  ret = mr1->init(data3);
  CPPUNIT_ASSERT_EQUAL(0, ret);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0, mr1->minSensor, 0.0001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0, mr1->maxSensor, 0.0001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0, mr1->maxSpeed, 0.0001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0, mr1->maxTurn, 0.0001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0, mr1->maxHardTurn, 0.0001);
	
	ret = mr1->init(data4); 
	CPPUNIT_ASSERT(ret != 0);
	ret = mr1->init(data5); 
	CPPUNIT_ASSERT(ret != 0);
	ret = mr1->init(data6); 
	CPPUNIT_ASSERT(ret != 0);
}

void RoverDataRegisterTest::testGetType() {
    ArgumentType type;
    int ret;

    ret = mr1->getType(&type, "Rover.Position");
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_EQUAL(POSITION, type);

    ret = mr1->getType(&type, "Rover.SpeedState");
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_EQUAL(INT, type);

    ret = mr1->getType(&type, "Rover.TurningState");
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_EQUAL(INT, type);

    ret = mr1->getType(&type, "Rover.Radius");
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_EQUAL(DOUBLE, type);

    ret = mr1->getType(&type, "Rover.Speed");
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_EQUAL(DOUBLE, type);

    ret = mr1->getType(&type, "Rover.MinSensor");
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_EQUAL(DOUBLE, type);

    ret = mr1->getType(&type, "Rover.MaxSensor");
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_EQUAL(DOUBLE, type);

    ret = mr1->getType(&type, "Rover.MaxSpeed");
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_EQUAL(DOUBLE, type);

    ret = mr1->getType(&type, "Rover.MaxTurn");
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_EQUAL(DOUBLE, type);

    ret = mr1->getType(&type, "Rover.MaxHardTurn");
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_EQUAL(DOUBLE, type);

    ret = mr1->getType(&type, "Rover.Heading");
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_EQUAL(DOUBLE, type);
  }

  void RoverDataRegisterTest::testGetValue() {
    int ret;
    Position pos(0, 0), pos_6_7(6, 7);
    double radius, speed, heading, minSensor, maxSensor;
    double maxSpeed, maxTurn, maxHardTurn;
    int speedState, turningState;
  	
    mr1->init("1.000 2.000 3.000 4.000 5.000;");
    mr1->parseRover("bL 6.000 7.000 8.000 9.000");

    ret = mr1->getValue(&pos, "Rover.Position");
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT(pos == pos_6_7);

    ret = mr1->getValue(&speedState, "Rover.SpeedState");
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_EQUAL(1, speedState);

    ret = mr1->getValue(&turningState, "Rover.TurningState");
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_EQUAL(1, turningState);

    ret = mr1->getValue(&radius, "Rover.Radius");
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.5, radius, 0.0001);

    ret = mr1->getValue(&speed, "Rover.Speed");
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(9, speed, 0.0001);

    ret = mr1->getValue(&minSensor, "Rover.MinSensor");
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1, minSensor, 0.0001);

    ret = mr1->getValue(&maxSensor, "Rover.MaxSensor");
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(2, maxSensor, 0.0001);

    ret = mr1->getValue(&maxSpeed, "Rover.MaxSpeed");
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(3, maxSpeed, 0.0001);

    ret = mr1->getValue(&maxTurn, "Rover.MaxTurn");
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(4, maxTurn, 0.0001);

    ret = mr1->getValue(&maxHardTurn, "Rover.MaxHardTurn");
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(5, maxHardTurn, 0.0001);

    ret = mr1->getValue(&heading, "Rover.Heading");
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(8, heading, 0.0001);
  }

void RoverDataRegisterTest::testSetValue() {
	int ret;
    Position pos(0, 0), pos_8_m4(8, -4);
    double radius=1.5, speed=2.5, heading=3.5, minSensor=4, maxSensor=5;
    double maxSpeed=6.3, maxTurn=7, maxHardTurn=0;
    int speedState=2, turningState=4;

    ret = mr1->setValue(&pos_8_m4, POSITION, "Rover.Position");
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT(mr1->pos == pos_8_m4);

    ret = mr1->setValue(&speedState, INT, "Rover.SpeedState");
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_EQUAL(speedState, mr1->speedState);

    ret = mr1->setValue(&turningState, INT, "Rover.TurningState");
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_EQUAL(turningState, mr1->turningState);

    ret = mr1->setValue(&radius, DOUBLE, "Rover.Radius");
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(radius, mr1->radius, 0.0001);

    ret = mr1->setValue(&speed, DOUBLE, "Rover.Speed");
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(speed, mr1->speed, 0.0001);

    ret = mr1->setValue(&heading, DOUBLE, "Rover.Heading");
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(heading, mr1->heading, 0.0001);

    //these cannot be set and should fail:
    ret = mr1->setValue(&minSensor, DOUBLE, "Rover.MinSensor");
    CPPUNIT_ASSERT(ret != 0);

    ret = mr1->setValue(&maxSensor, DOUBLE, "Rover.MaxSensor");
    CPPUNIT_ASSERT(ret != 0);

    ret = mr1->setValue(&maxSpeed, DOUBLE, "Rover.MaxSpeed");
    CPPUNIT_ASSERT(ret != 0);

    ret = mr1->setValue(&maxTurn, DOUBLE, "Rover.MaxTurn");
    CPPUNIT_ASSERT(ret != 0);

    ret = mr1->setValue(&maxHardTurn, DOUBLE, "Rover.MaxHardTurn");
    CPPUNIT_ASSERT(ret != 0);
}
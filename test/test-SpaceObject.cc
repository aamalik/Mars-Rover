#include "test-SpaceObject.h"
#include "ArgumentType.hh"

CPPUNIT_TEST_SUITE_REGISTRATION( SpaceObjectTest );

  void SpaceObjectTest::setUp() {
  	so_0_0_1_2_3 = new SpaceObject(0, 0, 1, 2, 3);
  	so_1_1_1_2_3 = new SpaceObject(1, 1, 1, 2, 3);
 	  so_1_m1_1_0_3 = new SpaceObject(1, -1, 1, 0, 3);
  }
  void SpaceObjectTest::tearDown() {
  	delete so_0_0_1_2_3;
  	delete so_1_1_1_2_3;
 	  delete so_1_m1_1_0_3;
  }
  void SpaceObjectTest::testConstructor() {

    CPPUNIT_ASSERT_DOUBLES_EQUAL(1, so_1_1_1_2_3->pos.getX(), 0.0001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1, so_1_1_1_2_3->pos.getY(), 0.0001);

    CPPUNIT_ASSERT_DOUBLES_EQUAL(1, so_1_m1_1_0_3->pos.getX(), 0.0001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(-1, so_1_m1_1_0_3->pos.getY(), 0.0001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1, so_1_m1_1_0_3->radius, 0.0001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0, so_1_m1_1_0_3->speed, 0.0001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(3, so_1_m1_1_0_3->heading, 0.0001);
  }
  void SpaceObjectTest::testGetType() {
    ArgumentType type;
    int ret;

    ret = so_0_0_1_2_3->getType(&type, "Position");
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_EQUAL(POSITION, type);

    ret = so_0_0_1_2_3->getType(&type, "Heading");
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_EQUAL(DOUBLE, type);

    ret = so_0_0_1_2_3->getType(&type, "Speed");
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_EQUAL(DOUBLE, type);

    ret = so_0_0_1_2_3->getType(&type, "Radius");
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_EQUAL(DOUBLE, type);

    ret = so_0_0_1_2_3->getType(&type, "X");
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_EQUAL(DOUBLE, type);

    ret = so_0_0_1_2_3->getType(&type, "Y");
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_EQUAL(DOUBLE, type);
  }

  void SpaceObjectTest::testSetValue() {
    int ret;
    double radius=6, speed=7, heading=8, x = 9, y = 11;
    Position pos1(3, 4), pos2(0, 0);
    SpaceObject test(2, 3, 4, 5, 6);
    ret = test.setValue(&radius, DOUBLE, "Radius");
    CPPUNIT_ASSERT_EQUAL(0, ret);
    ret = test.setValue(&speed, DOUBLE, "Speed");
    CPPUNIT_ASSERT_EQUAL(0, ret);
    ret = test.setValue(&heading, DOUBLE, "Heading");
    CPPUNIT_ASSERT_EQUAL(0, ret);
    ret = test.setValue(&pos1, POSITION, "Position");
    CPPUNIT_ASSERT_EQUAL(0, ret);

    CPPUNIT_ASSERT_DOUBLES_EQUAL(6, test.radius, 0.0001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(7, test.speed, 0.0001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(8, test.heading, 0.0001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(3, test.pos.getX(), 0.0001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(4, test.pos.getY(), 0.0001);

    ret = test.setValue(&x, DOUBLE, "X");
    CPPUNIT_ASSERT_EQUAL(0, ret);
    ret = test.setValue(&y, DOUBLE, "Y");
    CPPUNIT_ASSERT_EQUAL(0, ret);

    CPPUNIT_ASSERT_DOUBLES_EQUAL(9, test.pos.getX(), 0.0001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(11, test.pos.getY(), 0.0001);
  }
  
  void SpaceObjectTest::testGetValue() {
    Position pos(0, 0);
    double radius, speed, heading, x, y;
    SpaceObject test(-1, -2, 10, 11, 12);
  	test.getValue(&pos, "Position");
  	test.getValue(&radius, "Radius");
  	test.getValue(&speed, "Speed");
  	test.getValue(&heading, "Heading");
    test.getValue(&x, "X");
    test.getValue(&y, "Y");

  	CPPUNIT_ASSERT_DOUBLES_EQUAL(-1, pos.getX(), 0.0001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(-2, pos.getY(), 0.0001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(-1, x, 0.0001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(-2, y, 0.0001);
  	CPPUNIT_ASSERT_DOUBLES_EQUAL(10, radius, 0.0001);
  	CPPUNIT_ASSERT_DOUBLES_EQUAL(11, speed, 0.0001);
  	CPPUNIT_ASSERT_DOUBLES_EQUAL(12, heading, 0.0001);
  }
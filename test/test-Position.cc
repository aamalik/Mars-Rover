#include "test-Position.h"

CPPUNIT_TEST_SUITE_REGISTRATION( PositionTest );

void PositionTest::setUp() {
	p_0_0 = new Position(0, 0);
	p_0_0_2 = new Position(0, 0);
	p_1_0 = new Position(1, 0);
	p_1_0_2 = new Position(1, 0);
	p_0_1 = new Position(0, 1);
	p_m1_0 = new Position(-1, 0);
	p_0_m1 = new Position(0, -1);
	p_5_m5 = new Position(5, -5);
	p_5_m5_2 = new Position(5, -5);
}

void PositionTest::tearDown() {
	delete p_0_0;
	delete p_0_0_2;
	delete p_1_0;
	delete p_1_0_2;
	delete p_0_1;
	delete p_m1_0;
	delete p_0_m1;
	delete p_5_m5;
	delete p_5_m5_2;
}

void PositionTest::testConstructor() {
	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, p_0_0->getX(), 0.0001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, p_0_0->getY(), 0.0001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(1, p_1_0->getX(), 0.0001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(5, p_5_m5->getX(), 0.0001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(-1, p_m1_0->getX(), 0.0001);
}

void PositionTest::testOperators() {
	CPPUNIT_ASSERT(*p_0_0 == *p_0_0_2);
	CPPUNIT_ASSERT(*p_1_0 == *p_1_0_2);
	CPPUNIT_ASSERT(*p_5_m5 == *p_5_m5_2);
	CPPUNIT_ASSERT(*p_0_0 != *p_1_0);
}
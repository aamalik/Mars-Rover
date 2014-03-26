#ifndef POSITION_TEST_H
#define POSITION_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <Position.hh>

class PositionTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( PositionTest );
  CPPUNIT_TEST( testConstructor );
  CPPUNIT_TEST( testOperators );
  CPPUNIT_TEST_SUITE_END();

  Position *p_0_0;
  Position *p_0_0_2;
  Position *p_1_0;
  Position *p_1_0_2;
  Position *p_0_1;
  Position *p_m1_0;
  Position *p_0_m1;
  Position *p_5_m5;
  Position *p_5_m5_2;

public:
  void setUp();
  void tearDown();
  void testConstructor();
  void testOperators();
};

#endif  // POSITION_TEST_H
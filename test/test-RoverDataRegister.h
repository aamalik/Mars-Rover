#ifndef ROVER_DATA_REGISTER_TEST_H
#define ROVER_DATA_REGISTER_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <RoverDataRegister.hh>

class RoverDataRegisterTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( RoverDataRegisterTest );
  CPPUNIT_TEST( testInit );
  CPPUNIT_TEST( testParseRover );
  CPPUNIT_TEST( testGetType );
  CPPUNIT_TEST( testGetValue );
  CPPUNIT_TEST( testSetValue );
  CPPUNIT_TEST_SUITE_END();

  RoverDataRegister *mr1;

public:
  void setUp();
  void tearDown();
  void testConstructor();
  void testGetType();
  void testGetValue();
  void testParseRover();
  void testSetValue();
  void testInit();
};

#endif  // ROVER_DATA_REGISTER_TEST_H
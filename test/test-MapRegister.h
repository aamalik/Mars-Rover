#ifndef MAP_REGISTER_TEST_H
#define MAP_REGISTER_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <MapRegister.hh>

class MapRegisterTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( MapRegisterTest );
  CPPUNIT_TEST( testParseMapDetails );
  CPPUNIT_TEST( testGetType );
  CPPUNIT_TEST( testGetValue );
  CPPUNIT_TEST( testSetValue );
  CPPUNIT_TEST_SUITE_END();

  MapRegister *mr1;

public:
  void setUp();
  void tearDown();
  void testConstructor();
  void testGetType();
  void testGetValue();
  void testParseMapDetails();
  void testSetValue();
};

#endif  // MAP_REGISTER_TEST_H
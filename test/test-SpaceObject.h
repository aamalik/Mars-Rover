#ifndef SPACE_OBJECT_TEST_H
#define SPACE_OBJECT_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <SpaceObject.hh>

class SpaceObjectTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( SpaceObjectTest );
  CPPUNIT_TEST( testConstructor );
  CPPUNIT_TEST( testSetValue );
  //now we know set value works, so we use it freely
  CPPUNIT_TEST( testGetType );
  CPPUNIT_TEST( testGetValue );
  CPPUNIT_TEST_SUITE_END();

  SpaceObject *so_0_0_1_2_3;
  SpaceObject *so_1_1_1_2_3;
  SpaceObject *so_1_m1_1_0_3;

public:
  void setUp();
  void tearDown();
  void testConstructor();
  void testGetType();
  void testSetValue();
  void testGetValue();
};

#endif  // SPACE_OBJECT_TEST_H
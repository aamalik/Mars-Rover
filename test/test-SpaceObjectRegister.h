#ifndef SPACE_OBJECT_REGISTER_TEST_H
#define SPACE_OBJECT_REGISTER_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <SpaceObjectRegister.hh>

class SpaceObjectRegisterTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( SpaceObjectRegisterTest );
  CPPUNIT_TEST( testContainsObject );
  //CPPUNIT_TEST( testConstructor );
  CPPUNIT_TEST( testParseSpaceObjects );
  CPPUNIT_TEST( testGetType );
  CPPUNIT_TEST( testGetValue );
  CPPUNIT_TEST( testSetValue );
  CPPUNIT_TEST_SUITE_END();

  SpaceObjectRegister *mr1;
  VariableRegister *vr1;
  SpaceObject *obj1, *obj2, *obj3, *obj4, *martian1, *martian2, *martian3, *martian4;

public:
  void setUp();
  void tearDown();
  void testContainsObject();
  void testConstructor();
  void testGetType();
  void testGetValue();
  void testParseSpaceObjects();
  void testSetValue();
};

#endif  // SPACE_OBJECT_REGISTER_TEST_H
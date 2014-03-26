#ifndef VARIABLE_REGISTER_TEST_H
#define VARIABLE_REGISTER_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <VariableRegister.hh>

class VariableRegisterTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( VariableRegisterTest );
  CPPUNIT_TEST( testConstructor );
  CPPUNIT_TEST( testSetValue );
  //now we know set value works, so we use it freely
  CPPUNIT_TEST( testGetType );
  CPPUNIT_TEST( testGetValue );
  CPPUNIT_TEST( testExistsValue );
  CPPUNIT_TEST( testDeleteValue );
  //last test:
  CPPUNIT_TEST( testClean );
  CPPUNIT_TEST_SUITE_END();

  VariableRegister *vr1;

public:
  void setUp();
  void tearDown();
  void testConstructor();
  void testGetType();
  void testSetValue();
  void testGetValue();
  void testDeleteValue();
  void testClean();
  void testExistsValue();
};

#endif  // VARIABLE_REGISTER_TEST_H
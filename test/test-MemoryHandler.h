#ifndef MEMORY_HANDLER_TEST_H
#define MEMORY_HANDLER_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <MemoryHandler.hh>

class MemoryHandlerTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( MemoryHandlerTest );
  CPPUNIT_TEST( testConstructor );
  CPPUNIT_TEST( testInit );
  CPPUNIT_TEST( testParseData );
  CPPUNIT_TEST( testGetType );
  CPPUNIT_TEST( testDeleteValue );
  CPPUNIT_TEST( testSetValue );
  CPPUNIT_TEST_SUITE_END();

  MemoryHandler *mh1;

public:
  void setUp();
  void tearDown();
  void testConstructor();
  void testGetType();
  void testDeleteValue();
  void testParseData();
  void testSetValue();
  void testInit();
};

#endif  // MEMORY_HANDLER_TEST_H
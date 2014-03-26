#ifndef INSTRUCTION_PUT_TEST_H
#define INSTRUCTION_PUT_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include "../include/Instruction_put.hh"
#include "../include/MemoryHandler.hh"

class Instruction_putTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( Instruction_putTest );
  CPPUNIT_TEST( testConstructor );
  CPPUNIT_TEST( testExecute );
  CPPUNIT_TEST_SUITE_END( );

public:
  void setUp();
  void testConstructor();
  void testExecute();
  void tearDown();


private: 
  Instruction_put *i1,*i2,*i3,*i4,*i5,*i6;
  MemoryHandler *mh;
};

#endif  // INSTRUCTION_put_TEST_H
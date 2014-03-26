#ifndef INSTRUCTION_RET_TEST_H
#define INSTRUCTION_RET_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include "../include/Instruction_ret.hh"
#include "../include/MemoryHandler.hh"

class Instruction_retTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( Instruction_retTest );
  CPPUNIT_TEST( testConstructor );
  CPPUNIT_TEST( testExecute );
  CPPUNIT_TEST_SUITE_END( );

public:
  void setUp();
  void testConstructor();
  void testExecute();
  void tearDown();


private: 
  Instruction_ret *i1,*i2,*i3;
  MemoryHandler *mh;
};

#endif  // INSTRUCTION_RET_TEST_H
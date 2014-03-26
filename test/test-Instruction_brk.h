#ifndef INSTRUCTION_BRK_TEST_H
#define INSTRUCTION_BRK_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include "../include/Instruction_brk.hh"
#include "../include/MemoryHandler.hh"

class Instruction_brkTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( Instruction_brkTest );
  CPPUNIT_TEST( testConstructor );
  CPPUNIT_TEST( testExecute );
  CPPUNIT_TEST_SUITE_END( );

public:
  void setUp();
  void testConstructor();
  void testExecute();
  void tearDown();


private: 
  Instruction_brk *i1;
  MemoryHandler *mh;
};

#endif  // INSTRUCTION_BRK_TEST_H
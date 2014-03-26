#ifndef INSTRUCTION_CLN_TEST_H
#define INSTRUCTION_CLN_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include "../include/Instruction_cln.hh"
#include "../include/MemoryHandler.hh"

class Instruction_clnTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( Instruction_clnTest );
  CPPUNIT_TEST( testConstructor );
  CPPUNIT_TEST( testExecute );
  CPPUNIT_TEST_SUITE_END( );

public:
  void setUp();
  void testConstructor();
  void testExecute();
  void tearDown();


private: 
  Instruction_cln *i1;
  MemoryHandler *mh;
};

#endif  // INSTRUCTION_CLN_TEST_H
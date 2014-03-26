#ifndef INSTRUCTION_WAT_TEST_H
#define INSTRUCTION_WAT_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include "../include/Instruction_wat.hh"
#include "../include/MemoryHandler.hh"

class Instruction_watTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( Instruction_watTest );
  CPPUNIT_TEST( testConstructor );
  CPPUNIT_TEST( testExecute );
  CPPUNIT_TEST_SUITE_END( );

public:
  void setUp();
  void testConstructor();
  void testExecute();
  void tearDown();


private: 
  Instruction_wat *i1;
  MemoryHandler *mh;
};

#endif  // INSTRUCTION_WAT_TEST_H
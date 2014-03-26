#ifndef INSTRUCTION_EBK_TEST_H
#define INSTRUCTION_EBK_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include "../include/Instruction_ebk.hh"
#include "../include/MemoryHandler.hh"

class Instruction_ebkTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( Instruction_ebkTest );
  CPPUNIT_TEST( testConstructor );
  CPPUNIT_TEST( testExecute );
  CPPUNIT_TEST_SUITE_END( );

public:
  void setUp();
  void testConstructor();
  void testExecute();
  void tearDown();


private: 
  Instruction_ebk *i1;
  MemoryHandler *mh;
};

#endif  // INSTRUCTION_EBK_TEST_H
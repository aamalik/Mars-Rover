#ifndef INSTRUCTION_JMP_TEST_H
#define INSTRUCTION_JMP_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include "../include/Instruction_jmp.hh"
#include "../include/MemoryHandler.hh"

class Instruction_jmpTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( Instruction_jmpTest );
  CPPUNIT_TEST( testConstructor );
  CPPUNIT_TEST( testExecute );
  CPPUNIT_TEST_SUITE_END( );

public:
  void setUp();
  void testConstructor();
  void testExecute();
  void tearDown();


private: 
  Instruction_jmp *i1,*i2,*i3,*i4;
  MemoryHandler *mh;
};

#endif  // INSTRUCTION_jmp_TEST_H
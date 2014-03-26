#ifndef INSTRUCTION_CRA_TEST_H
#define INSTRUCTION_CRA_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include "../include/Instruction_cra.hh"
#include "../include/MemoryHandler.hh"

class Instruction_craTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( Instruction_craTest );
  CPPUNIT_TEST( testConstructor );
  CPPUNIT_TEST( testExecute );
  CPPUNIT_TEST_SUITE_END( );

public:
  void setUp();
  void testConstructor();
  void testExecute();
  void tearDown();


private: 
  Instruction_cra *i1,*i2,*i3,*i4,*i5,*i6,*i7;
  MemoryHandler *mh;
};

#endif  // INSTRUCTION_CRA_TEST_H
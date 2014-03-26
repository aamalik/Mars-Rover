#ifndef INSTRUCTION_DIV_TEST_H
#define INSTRUCTION_DIV_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include "../include/Instruction_div.hh"
#include "../include/MemoryHandler.hh"

class Instruction_divTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( Instruction_divTest );
  CPPUNIT_TEST( testConstructor );
  CPPUNIT_TEST( testExecute );
  CPPUNIT_TEST_SUITE_END( );

public:
  void setUp();
  void testConstructor();
  void testExecute();
  void tearDown();


private: 
  Instruction_div *i1,*i2,*i3,*i4,*i5,*i6,*i7;
  MemoryHandler *mh;
};

#endif  // INSTRUCTION_DIV_TEST_H
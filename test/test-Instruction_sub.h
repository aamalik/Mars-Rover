#ifndef INSTRUCTION_SUB_TEST_H
#define INSTRUCTION_SUB_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include "../include/Instruction_sub.hh"
#include "../include/MemoryHandler.hh"

class Instruction_subTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( Instruction_subTest );
  CPPUNIT_TEST( testConstructor );
  CPPUNIT_TEST( testExecute );
  CPPUNIT_TEST_SUITE_END( );

public:
  void setUp();
  void testConstructor();
  void testExecute();
  void tearDown();


private: 
  Instruction_sub *i1,*i2,*i3,*i4,*i5,*i6,*i7;
  MemoryHandler *mh;
};

#endif  // INSTRUCTION_SUB_TEST_H
#ifndef INSTRUCTION_ADD_TEST_H
#define INSTRUCTION_ADD_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include "../include/Instruction_add.hh"
#include "../include/MemoryHandler.hh"

class Instruction_addTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( Instruction_addTest );
  CPPUNIT_TEST( testConstructor );
  CPPUNIT_TEST( testExecute );
  CPPUNIT_TEST_SUITE_END( );

public:
  void setUp();
  void testConstructor();
  void testExecute();
  void tearDown();


private: 
  Instruction_add *i1,*i2,*i3,*i4,*i5,*i6,*i7;
  MemoryHandler *mh;
};

#endif  // INSTRUCTION_ADD_TEST_H
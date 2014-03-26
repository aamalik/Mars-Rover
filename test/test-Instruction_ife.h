#ifndef INSTRUCTION_IFE_TEST_H
#define INSTRUCTION_IFE_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include "../include/Instruction_ife.hh"
#include "../include/MemoryHandler.hh"

class Instruction_ifeTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( Instruction_ifeTest );
  CPPUNIT_TEST( testConstructor );
  CPPUNIT_TEST( testExecute );
  CPPUNIT_TEST_SUITE_END( );

public:
  void setUp();
  void testConstructor();
  void testExecute();
  void tearDown();


private: 
  Instruction_ife *i1,*i2,*i3,*i4,*i5,*i6,*i7,*i8,*i9,*i10,*i11;
  MemoryHandler *mh;
};

#endif  // INSTRUCTION_IFE_TEST_H
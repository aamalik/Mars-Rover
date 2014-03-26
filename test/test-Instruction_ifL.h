#ifndef INSTRUCTION_IFBIGL_TEST_H
#define INSTRUCTION_IFBIGL_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include "../include/Instruction_ifL.hh"
#include "../include/MemoryHandler.hh"

class Instruction_ifLTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( Instruction_ifLTest );
  CPPUNIT_TEST( testConstructor );
  CPPUNIT_TEST( testExecute );
  CPPUNIT_TEST_SUITE_END( );

public:
  void setUp();
  void testConstructor();
  void testExecute();
  void tearDown();


private: 
  Instruction_ifL *i1,*i2,*i3,*i4,*i5,*i6,*i7,*i8,*i9,*i10,*i11;
  MemoryHandler *mh;
};

#endif  // INSTRUCTION_ifL_TEST_H
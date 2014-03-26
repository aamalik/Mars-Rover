#ifndef INSTRUCTION_CRT_TEST_H
#define INSTRUCTION_CRT_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include "../include/Instruction_crt.hh"
#include "../include/MemoryHandler.hh"

class Instruction_crtTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( Instruction_crtTest );
  CPPUNIT_TEST( testConstructor );
  CPPUNIT_TEST( testExecute );
  CPPUNIT_TEST_SUITE_END( );

public:
  void setUp();
  void testConstructor();
  void testExecute();
  void tearDown();


private: 
  Instruction_crt *i1,*i2,*i3,*i4,*i5,*i6;
  MemoryHandler *mh;
};

#endif  // INSTRUCTION_CRT_TEST_H
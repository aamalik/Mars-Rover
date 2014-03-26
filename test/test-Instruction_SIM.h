#ifndef _TEST_INSTRUCTION_SIM_HH
#define _TEST_INSTRUCTION_SIM_HH

#include <cppunit/extensions/HelperMacros.h>

#include "Position.hh"
#include "SpaceObject.hh"

class TestInstructionSIM : public CppUnit::TestFixture{

  CPPUNIT_TEST_SUITE(TestInstructionSIM);
  CPPUNIT_TEST(testInstructionSIM);
  CPPUNIT_TEST_SUITE_END();

 public:
  void setUp();
  void tearDown();
  void testInstructionSIM();
  Position calculatePosition(SpaceObject obj,int time,double speed);
};

#endif

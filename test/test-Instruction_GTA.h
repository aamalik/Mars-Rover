/**
 * @file test-Instruction_GTA
 * @brief Test cases for the Instruction_GAP
 */ 
#ifndef TEST_GTA_HH
#define TEST_GTA_HH

#include <cppunit/extensions/HelperMacros.h>
#include <string>
#include <map>
#include "Brain.hh"
#include "InstructionIF.hh"
#include "Position.hh"

using namespace std;

class TestInstructionGTA : public CppUnit::TestFixture{
  
  CPPUNIT_TEST_SUITE(TestInstructionGTA);
  CPPUNIT_TEST(testInstructionGTA);
  CPPUNIT_TEST_SUITE_END();

 public:
  void setUp();
  void tearDown();
  void testInstructionGTA();
  double calcAngle(Position p);
};

#endif

/**
 * @file test-Brain
 * @brief Test cases for the Brain.
*/ 
#ifndef TEST_BRAIN_HH
#define TEST_BRAIN_HH

#include <cppunit/extensions/HelperMacros.h>
#include <string>
#include <map>
#include "Brain.hh"
#include "InstructionIF.hh"

using namespace std;

class BrainTest : public CppUnit::TestFixture{

  CPPUNIT_TEST_SUITE(BrainTest);
  CPPUNIT_TEST(testParseData);
  CPPUNIT_TEST_SUITE_END();
  Brain * brain; 
  vector<InstructionIF*> code;

 public:
  void setUp();
  void tearDown();
  void testParseData();
  void testInitBrain();
};

#endif

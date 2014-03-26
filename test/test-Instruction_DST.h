#ifndef TEST_INSTRUCTION_DST_HH
#define TEST_INSTRUCTION_DST_HH

#include <cppunit/extensions/HelperMacros.h>
#include <string>
#include <map>

using namespace std;

class InstructionDSTTest : public CppUnit::TestFixture{

  CPPUNIT_TEST_SUITE(InstructionDSTTest);
  CPPUNIT_TEST(testDST);
  CPPUNIT_TEST_SUITE_END();

 public:
  void setUp();
  void tearDown();
  void testDST();

};

#endif

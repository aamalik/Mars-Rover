#ifndef TEST_INSTRUCTION_GAP_HH
#define TEST_INSTRUCTION_GAP_HH

#include <cppunit/extensions/HelperMacros.h>
#include <string>
#include <map>

#include "Position.hh"
#include "SpaceObject.hh"

using namespace std;

class InstructionGAPTest : public CppUnit::TestFixture{

  CPPUNIT_TEST_SUITE(InstructionGAPTest);
  CPPUNIT_TEST(testGAP);
  CPPUNIT_TEST_SUITE_END();

 public:
  void setUp();
  void tearDown();
  void testGAP();
  void createAllPossibilities(map<string,Position> &positions,SpaceObject obj,int time, double maxTurn, double maxSpeed);
  void validateResults(map<string,Position> &pos,string * names,Position * dirs,int size);
};


#endif

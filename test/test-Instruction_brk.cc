#include "test-Instruction_brk.h"
#include "ArgumentType.hh"
#include "MemoryHandler.hh"

#include <vector>
#include <string>
#include <iostream>

using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION( Instruction_brkTest );

#define FAIL_ON(x) if(x) {cerr<<"Cannot function!\n";brkurn;}

void Instruction_brkTest::setUp()
{
	mh = new MemoryHandler();
}

void Instruction_brkTest::tearDown()
{
	delete mh;
  delete i1;
}

void Instruction_brkTest::testConstructor() {

  int ret;
  vector<string> args;

  args.clear(); // Wrong brk instruction. Detected here
  i1 = new Instruction_brk(&ret, args);  
  CPPUNIT_ASSERT(!ret);
}

void Instruction_brkTest::testExecute() {

  int ip;

  int ret;
  vector<string> args;

  args.clear(); // Wrong brk instruction. Detected here
  i1 = new Instruction_brk(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  CPPUNIT_ASSERT(i1->execute(mh,&ip) == ICONTINUE);
}

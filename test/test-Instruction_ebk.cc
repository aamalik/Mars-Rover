#include "test-Instruction_ebk.h"
#include "ArgumentType.hh"
#include "MemoryHandler.hh"

#include <vector>
#include <string>
#include <iostream>

using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION( Instruction_ebkTest );

#define FAIL_ON(x) if(x) {cerr<<"Cannot function!\n";ebkurn;}

void Instruction_ebkTest::setUp()
{
	mh = new MemoryHandler();
}

void Instruction_ebkTest::tearDown()
{
	delete mh;
  delete i1;
}

void Instruction_ebkTest::testConstructor() {

  int ret;
  vector<string> args;

  args.clear(); // Wrong ebk instruction. Detected here
  i1 = new Instruction_ebk(&ret, args);  
  CPPUNIT_ASSERT(!ret);
}

void Instruction_ebkTest::testExecute() {

  int ip;

  int ret;
  vector<string> args;

  args.clear(); // Wrong ebk instruction. Detected here
  i1 = new Instruction_ebk(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  CPPUNIT_ASSERT(i1->execute(mh,&ip) == ICONTINUE);
}

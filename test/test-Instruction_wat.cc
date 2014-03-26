#include "test-Instruction_wat.h"
#include "ArgumentType.hh"
#include "MemoryHandler.hh"

#include <vector>
#include <string>
#include <iostream>

using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION( Instruction_watTest );

#define FAIL_ON(x) if(x) {cerr<<"Cannot function!\n";waturn;}

void Instruction_watTest::setUp()
{
	mh = new MemoryHandler();
}

void Instruction_watTest::tearDown()
{
	delete mh;
  delete i1;
}

void Instruction_watTest::testConstructor() {

  int ret;
  vector<string> args;

  args.clear(); // Wrong wat instruction. Detected here
  i1 = new Instruction_wat(&ret, args);  
  CPPUNIT_ASSERT(!ret);
}

void Instruction_watTest::testExecute() {

  int ip;

  int ret;
  vector<string> args;

  args.clear(); // Wrong wat instruction. Detected here
  i1 = new Instruction_wat(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  CPPUNIT_ASSERT(i1->execute(mh,&ip) == IWAIT);
}

#include "test-Instruction_cln.h"
#include "ArgumentType.hh"
#include "MemoryHandler.hh"

#include <vector>
#include <string>
#include <iostream>

using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION( Instruction_clnTest );

#define FAIL_ON(x) if(x) {cerr<<"Cannot function!\n";clnurn;}

void Instruction_clnTest::setUp()
{
	mh = new MemoryHandler();
  int i;
  double d;
  int ret;

  i=1;
  ret = mh->setValue((void*)&i,INT,"ivar"); 
  CPPUNIT_ASSERT(!ret);
  d = 2.0;
  ret = mh->setValue((void*)&d,DOUBLE,"dvar"); 
  CPPUNIT_ASSERT(!ret);
}

void Instruction_clnTest::tearDown()
{
	delete mh;
  delete i1;
}

void Instruction_clnTest::testConstructor() {

  int ret;
  vector<string> args;

  args.clear(); // Wrong cln instruction. Detected here
  i1 = new Instruction_cln(&ret, args);  
  CPPUNIT_ASSERT(!ret);
}

void Instruction_clnTest::testExecute() {

  int ip;
  ArgumentType t;

  int ret;
  vector<string> args;

  args.clear(); // Wrong cln instruction. Detected here
  i1 = new Instruction_cln(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  CPPUNIT_ASSERT(!mh->getType(&t,"ivar"));
  CPPUNIT_ASSERT(!mh->getType(&t,"dvar"));
  CPPUNIT_ASSERT(!i1->execute(mh,&ip));
  CPPUNIT_ASSERT(mh->getType(&t,"ivar"));
  CPPUNIT_ASSERT(mh->getType(&t,"dvar"));
}

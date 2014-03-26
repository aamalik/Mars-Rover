#include "test-Instruction_ret.h"
#include "ArgumentType.hh"
#include "MemoryHandler.hh"

#include <vector>
#include <string>
#include <iostream>

using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION( Instruction_retTest );

#define FAIL_ON(x) if(x) {cerr<<"Cannot function!\n";return;}

void Instruction_retTest::setUp()
{
	mh = new MemoryHandler();
  string s;
  int ret;

  s = "a";
  ret = mh->setValue((void*)&s,STRING,"svar"); 
  CPPUNIT_ASSERT(!ret);
}

void Instruction_retTest::tearDown()
{
	delete mh;
  delete i1;
  delete i2;
  delete i3;
}

void Instruction_retTest::testConstructor() {

  int ret;
  vector<string> args;

  args.clear(); // Correct String ret
  args.push_back("svar");
  i1 = new Instruction_ret(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Wrong ret instruction . Will be detected at execute time
  args.push_back("Map.Length");
  i2 = new Instruction_ret(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Wrong ret instruction. Detected here
  i3 = new Instruction_ret(&ret, args);  
  CPPUNIT_ASSERT(ret);
}

void Instruction_retTest::testExecute() {

  int ip;

  int ret;
  vector<string> args;

  args.clear(); // Correct String ret
  args.push_back("svar");
  i1 = new Instruction_ret(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Wrong ret instruction . Will be detected at execute time
  args.push_back("Map.Length");
  i2 = new Instruction_ret(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Wrong ret instruction. Detected here
  i3 = new Instruction_ret(&ret, args);  
  CPPUNIT_ASSERT(ret);

  CPPUNIT_ASSERT(i1->execute(mh,&ip) == IRETURN);
  string s = mh->getReturnString();
  CPPUNIT_ASSERT(s == "a;");

  CPPUNIT_ASSERT(i2->execute(mh,&ip));
}

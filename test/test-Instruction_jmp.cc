#include "test-Instruction_jmp.h"
#include "ArgumentType.hh"
#include "MemoryHandler.hh"

#include <vector>
#include <string>
#include <iostream>

using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION( Instruction_jmpTest );

#define FAIL_ON(x) if(x) {cerr<<"Cannot function!\n";return;}

void Instruction_jmpTest::setUp()
{
	mh = new MemoryHandler();

}

void Instruction_jmpTest::tearDown()
{
	delete mh;
  delete i1;
  delete i2;
  delete i3;
  delete i4;
}

void Instruction_jmpTest::testConstructor() {

  int ret;
  vector<string> args;

  args.clear(); // Correct jmp
  args.push_back("100");
  i1 = new Instruction_jmp(&ret, args);
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Correct jmp
  args.push_back("200");
  i2 = new Instruction_jmp(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Wrong jmp instruction . Detected here
  args.push_back("-50");
  i3 = new Instruction_jmp(&ret, args);  
  CPPUNIT_ASSERT(ret);

  args.clear(); // Wrong jmp instruction. Detected here
  args.push_back("100");
  args.push_back("200");
  i4 = new Instruction_jmp(&ret, args);  
  CPPUNIT_ASSERT(ret);
}

void Instruction_jmpTest::testExecute() {

  int ip;

  int ret;
  vector<string> args;

  args.clear(); // Correct jmp
  args.push_back("100");
  i1 = new Instruction_jmp(&ret, args);
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Correct jmp
  args.push_back("200");
  i2 = new Instruction_jmp(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Wrong jmp instruction . Detected here
  args.push_back("-50");
  i3 = new Instruction_jmp(&ret, args);  
  CPPUNIT_ASSERT(ret);

  args.clear(); // Wrong jmp instruction. Detected here
  args.push_back("100");
  args.push_back("200");
  i4 = new Instruction_jmp(&ret, args);  
  CPPUNIT_ASSERT(ret);

  ip = 0;
  CPPUNIT_ASSERT(!i1->execute(mh,&ip));
  CPPUNIT_ASSERT_EQUAL(100, ip);

  ip = 0;
  CPPUNIT_ASSERT(!i2->execute(mh,&ip));
  CPPUNIT_ASSERT_EQUAL(200, ip);

}

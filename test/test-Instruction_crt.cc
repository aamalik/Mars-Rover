#include "test-Instruction_crt.h"
#include "ArgumentType.hh"
#include "MemoryHandler.hh"

#include <vector>
#include <string>
#include <iostream>

using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION( Instruction_crtTest );

#define FAIL_ON(x) if(x) {cerr<<"Cannot function!\n";return;}

void Instruction_crtTest::setUp()
{
	mh = new MemoryHandler();
}

void Instruction_crtTest::tearDown()
{
	delete mh;
  delete i1;
  delete i2;
  delete i3;
  delete i4;
  delete i5;
  delete i6;
}

void Instruction_crtTest::testConstructor() {

  int ret;
  vector<string> args;

  args.clear(); // Correct int crt
  args.push_back("*Int");
  args.push_back("*i");
  i1 = new Instruction_crt(&ret, args);
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Correct double crt
  args.push_back("*Double");
  args.push_back("*d");
  i2 = new Instruction_crt(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Correct Position crt
  args.push_back("*Position");
  args.push_back("*p");
  i3 = new Instruction_crt(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Correct String crt
  args.push_back("*String");
  args.push_back("*s");
  i4 = new Instruction_crt(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Wrong crt instruction . Detected here
  args.push_back("novar");
  i5 = new Instruction_crt(&ret, args);  
  CPPUNIT_ASSERT(ret);

  args.clear(); // Wrong crt instruction. Detected here
  args.push_back("x");
  i6 = new Instruction_crt(&ret, args);  
  CPPUNIT_ASSERT(ret);

}

void Instruction_crtTest::testExecute() {

  int ip;
  int iv;
  double dv;
  Position pv;
  string sv;
  ArgumentType t = NOTYPE;

  int ret;
  vector<string> args;

  args.clear(); // Correct int crt
  args.push_back("*Int");
  args.push_back("*i");
  i1 = new Instruction_crt(&ret, args);
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Correct double crt
  args.push_back("*Double");
  args.push_back("*d");
  i2 = new Instruction_crt(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Correct Position crt
  args.push_back("*Position");
  args.push_back("*p");
  i3 = new Instruction_crt(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Correct String crt
  args.push_back("*String");
  args.push_back("*s");
  i4 = new Instruction_crt(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Wrong crt instruction . Detected here
  args.push_back("novar");
  i5 = new Instruction_crt(&ret, args);  
  CPPUNIT_ASSERT(ret);

  args.clear(); // Wrong crt instruction. Detected here
  args.push_back("x");
  i6 = new Instruction_crt(&ret, args);  
  CPPUNIT_ASSERT(ret);

  CPPUNIT_ASSERT(!i1->execute(mh,&ip));
  CPPUNIT_ASSERT(!mh->getType(&t,"i"));
  CPPUNIT_ASSERT( t == INT );
  CPPUNIT_ASSERT(!mh->getValue((void*)&iv,"i"));
  CPPUNIT_ASSERT_EQUAL(iv, 0);

  CPPUNIT_ASSERT(!i2->execute(mh,&ip));
  CPPUNIT_ASSERT(!mh->getType(&t,"d"));
  CPPUNIT_ASSERT( t == DOUBLE );
  CPPUNIT_ASSERT(!mh->getValue((void*)&dv,"d"));
  CPPUNIT_ASSERT_EQUAL(dv, 0.0);

  CPPUNIT_ASSERT(!i3->execute(mh,&ip));
  CPPUNIT_ASSERT(!mh->getType(&t,"p"));
  CPPUNIT_ASSERT( t == POSITION );
  CPPUNIT_ASSERT(!mh->getValue((void*)&pv,"p"));
  CPPUNIT_ASSERT_EQUAL(pv.getX(), 0.0);
  CPPUNIT_ASSERT_EQUAL(pv.getY(), 0.0);

  CPPUNIT_ASSERT(!i4->execute(mh,&ip));
  CPPUNIT_ASSERT(!mh->getType(&t,"s"));
  CPPUNIT_ASSERT( t == STRING );
  CPPUNIT_ASSERT(!mh->getValue((void*)&sv,"s"));
  CPPUNIT_ASSERT( sv == "" );

}

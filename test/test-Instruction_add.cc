#include "test-Instruction_add.h"
#include "ArgumentType.hh"
#include "MemoryHandler.hh"

#include <vector>
#include <string>
#include <iostream>

using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION( Instruction_addTest );

#define FAIL_ON(x) if(x) {cerr<<"Cannot function!\n";return;}

void Instruction_addTest::setUp()
{
	mh = new MemoryHandler();
  int i ;
  double d;
  Position p;
  int ret;
 // string s;

  i = 10;
  ret = mh->setValue((void*)&i,INT,"aivar"); 
  CPPUNIT_ASSERT(!ret);
  i = 20;
  ret = mh->setValue((void*)&i,INT,"bivar"); 
  CPPUNIT_ASSERT(!ret);
  i = 10;
  ret = mh->setValue((void*)&i,INT,"civar"); 
  CPPUNIT_ASSERT(!ret);

  d = 0.12;
  ret = mh->setValue((void*)&d,DOUBLE,"advar"); 
  CPPUNIT_ASSERT(!ret);
  d = 100.02;
  ret = mh->setValue((void*)&d,DOUBLE,"bdvar"); 
  CPPUNIT_ASSERT(!ret);
  d = 0.0;
  ret = mh->setValue((void*)&d,DOUBLE,"cdvar"); 
  CPPUNIT_ASSERT(!ret);

  p = Position(1,2);
  ret = mh->setValue((void*)&p,POSITION,"apvar");
  CPPUNIT_ASSERT(!ret);
  p = Position(3,4);
  ret = mh->setValue((void*)&p,POSITION,"bpvar");
  CPPUNIT_ASSERT(!ret);
  p = Position(0,0);
  ret = mh->setValue((void*)&p,POSITION,"cpvar");
  CPPUNIT_ASSERT(!ret);
}

void Instruction_addTest::tearDown()
{
	delete mh;
  delete i1;
  delete i2;
  delete i3;
  delete i4;
  delete i5;
  delete i6;
  delete i7;
}

void Instruction_addTest::testConstructor() {

  int ret;
  vector<string> args;

  args.clear(); // Correct int add
  args.push_back("civar");
  args.push_back("20");
  args.push_back("aivar");
  i1 = new Instruction_add(&ret, args);
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Correct double add
  args.push_back("cdvar");
  args.push_back("100.02");
  args.push_back("advar");
  i2 = new Instruction_add(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Correct Position add
  args.push_back("cpvar");
  args.push_back("bpvar");
  args.push_back("apvar");
  i3 = new Instruction_add(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Wrong add instruction . Will be detected at execute time
  args.push_back("cvar");
  args.push_back("bdvar");
  args.push_back("advar");
  i4 = new Instruction_add(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Wrong add instruction . Will be detected at execute time
  args.push_back("cpvar");
  args.push_back("bdvar");
  args.push_back("aivar");
  i5 = new Instruction_add(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Wrong add instruction . Will be detected at execute time
  args.push_back("aivar");
  args.push_back("aivar");
  args.push_back("advar");
  i6 = new Instruction_add(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Wrong add instruction. Detected here
  args.push_back("cvar");
  args.push_back("bdvar");
  i7 = new Instruction_add(&ret, args);  
  CPPUNIT_ASSERT(ret);

}

void Instruction_addTest::testExecute() {

  int ip;
  int iv;
  double dv;
  Position pv;

  int ret;
  vector<string> args;

  args.clear(); // Correct int add
  args.push_back("civar");
  args.push_back("bivar");
  args.push_back("aivar");
  i1 = new Instruction_add(&ret, args);
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Correct double add
  args.push_back("cdvar");
  args.push_back("bdvar");
  args.push_back("advar");
  i2 = new Instruction_add(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Correct Position add
  args.push_back("cpvar");
  args.push_back("bpvar");
  args.push_back("apvar");
  i3 = new Instruction_add(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Wrong add instruction . Will be detected at execute time
  args.push_back("cvar");
  args.push_back("bdvar");
  args.push_back("advar");
  i4 = new Instruction_add(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Wrong add instruction . Will be detected at execute time
  args.push_back("cpvar");
  args.push_back("bdvar");
  args.push_back("aivar");
  i5 = new Instruction_add(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Wrong add instruction . Will be detected at execute time
  args.push_back("aivar");
  args.push_back("aivar");
  args.push_back("advar");
  i6 = new Instruction_add(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Wrong add instruction. Detected here
  args.push_back("cvar");
  args.push_back("bdvar");
  i7 = new Instruction_add(&ret, args);  
  CPPUNIT_ASSERT(ret);

  CPPUNIT_ASSERT(!i1->execute(mh,&ip));
  CPPUNIT_ASSERT(!mh->getValue((void*)&iv,"civar"));
  CPPUNIT_ASSERT_EQUAL(iv, 30);

  CPPUNIT_ASSERT(!i2->execute(mh,&ip));
  CPPUNIT_ASSERT(!mh->getValue((void*)&dv,"cdvar"));
  CPPUNIT_ASSERT_EQUAL(dv, 100.14);

  CPPUNIT_ASSERT(!i3->execute(mh,&ip));
  CPPUNIT_ASSERT(!mh->getValue((void*)&pv,"cpvar"));
  CPPUNIT_ASSERT_EQUAL(pv.getX(), 4.0);
  CPPUNIT_ASSERT_EQUAL(pv.getY(), 6.0);

  CPPUNIT_ASSERT(i4->execute(mh,&ip));
  CPPUNIT_ASSERT(i5->execute(mh,&ip));
  CPPUNIT_ASSERT(i6->execute(mh,&ip));
  CPPUNIT_ASSERT(i7->execute(mh,&ip));
}

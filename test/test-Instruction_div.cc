#include "test-Instruction_div.h"
#include "ArgumentType.hh"
#include "MemoryHandler.hh"

#include <vector>
#include <string>
#include <iostream>

using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION( Instruction_divTest );

#define FAIL_ON(x) if(x) {cerr<<"Cannot function!\n";return;}

void Instruction_divTest::setUp()
{
	mh = new MemoryHandler();
  int i ;
  double d;
  Position p;
  int ret;
 // string s;

  i = 7;
  ret = mh->setValue((void*)&i,INT,"aivar"); 
  CPPUNIT_ASSERT(!ret);
  i = 17;
  ret = mh->setValue((void*)&i,INT,"bivar"); 
  CPPUNIT_ASSERT(!ret);
  i = 0; // 17 / 7 = 2
  ret = mh->setValue((void*)&i,INT,"civar"); 
  CPPUNIT_ASSERT(!ret);

  d = 4.20;
  ret = mh->setValue((void*)&d,DOUBLE,"advar"); 
  CPPUNIT_ASSERT(!ret);
  d = 3.14; // 3.14 / 4.20 = 0.747619048
  ret = mh->setValue((void*)&d,DOUBLE,"bdvar"); 
  CPPUNIT_ASSERT(!ret);
  d = 0.0;
  ret = mh->setValue((void*)&d,DOUBLE,"cdvar"); 
  CPPUNIT_ASSERT(!ret);

  d = 4.0;
  ret = mh->setValue((void*)&d,DOUBLE,"apvar");
  CPPUNIT_ASSERT(!ret);
  p = Position(1,4);
  ret = mh->setValue((void*)&p,POSITION,"bpvar");
  CPPUNIT_ASSERT(!ret);
  p = Position(0,0); // (1,4) / 4 = (0.25, 1)
  ret = mh->setValue((void*)&p,POSITION,"cpvar");
  CPPUNIT_ASSERT(!ret);
}

void Instruction_divTest::tearDown()
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

void Instruction_divTest::testConstructor() {

  int ret;
  vector<string> args;

  args.clear(); // Correct int div
  args.push_back("civar");
  args.push_back("bivar");
  args.push_back("aivar");
  i1 = new Instruction_div(&ret, args);
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Correct double div
  args.push_back("cdvar");
  args.push_back("bdvar");
  args.push_back("advar");
  i2 = new Instruction_div(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Correct Position div
  args.push_back("cpvar");
  args.push_back("bpvar");
  args.push_back("apvar");
  i3 = new Instruction_div(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Wrong div instruction . Will be detected at execute time
  args.push_back("cvar");
  args.push_back("bdvar");
  args.push_back("advar");
  i4 = new Instruction_div(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Wrong div instruction . Will be detected at execute time
  args.push_back("cpvar");
  args.push_back("bdvar");
  args.push_back("aivar");
  i5 = new Instruction_div(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Wrong div instruction . Will be detected at execute time
  args.push_back("aivar");
  args.push_back("aivar");
  args.push_back("advar");
  i6 = new Instruction_div(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Wrong div instruction. Detected here
  args.push_back("cvar");
  args.push_back("bdvar");
  i7 = new Instruction_div(&ret, args);  
  CPPUNIT_ASSERT(ret);

}

void Instruction_divTest::testExecute() {

  int ip;
  int iv;
  double dv;
  Position pv;

  int ret;
  vector<string> args;

  args.clear(); // Correct int div
  args.push_back("civar");
  args.push_back("bivar");
  args.push_back("aivar");
  i1 = new Instruction_div(&ret, args);
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Correct double div
  args.push_back("cdvar");
  args.push_back("bdvar");
  args.push_back("advar");
  i2 = new Instruction_div(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Correct Position div
  args.push_back("cpvar");
  args.push_back("bpvar");
  args.push_back("apvar");
  i3 = new Instruction_div(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Wrong div instruction . Will be detected at execute time
  args.push_back("cvar");
  args.push_back("bdvar");
  args.push_back("advar");
  i4 = new Instruction_div(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Wrong div instruction . Will be detected at execute time
  args.push_back("cpvar");
  args.push_back("bdvar");
  args.push_back("aivar");
  i5 = new Instruction_div(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Wrong div instruction . Will be detected at execute time
  args.push_back("aivar");
  args.push_back("aivar");
  args.push_back("advar");
  i6 = new Instruction_div(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Wrong div instruction. Detected here
  args.push_back("cvar");
  args.push_back("bdvar");
  i7 = new Instruction_div(&ret, args);  
  CPPUNIT_ASSERT(ret);

  CPPUNIT_ASSERT(!i1->execute(mh,&ip));
  CPPUNIT_ASSERT(!mh->getValue((void*)&iv,"civar"));
  CPPUNIT_ASSERT_EQUAL(iv, 2);

  CPPUNIT_ASSERT(!i2->execute(mh,&ip));
  CPPUNIT_ASSERT(!mh->getValue((void*)&dv,"cdvar"));
  CPPUNIT_ASSERT_DOUBLES_EQUAL(dv, 0.747619048,0.000001);

  CPPUNIT_ASSERT(!i3->execute(mh,&ip));
  CPPUNIT_ASSERT(!mh->getValue((void*)&pv,"cpvar"));
  CPPUNIT_ASSERT_EQUAL(pv.getX(), 0.25);
  CPPUNIT_ASSERT_EQUAL(pv.getY(), 1.0);

  CPPUNIT_ASSERT(i4->execute(mh,&ip));
  CPPUNIT_ASSERT(i5->execute(mh,&ip));
  CPPUNIT_ASSERT(i6->execute(mh,&ip));
  CPPUNIT_ASSERT(i7->execute(mh,&ip));
}

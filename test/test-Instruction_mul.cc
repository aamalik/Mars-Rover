#include "test-Instruction_mul.h"
#include "ArgumentType.hh"
#include "MemoryHandler.hh"

#include <vector>
#include <string>
#include <iostream>

using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION( Instruction_mulTest );

#define FAIL_ON(x) if(x) {cerr<<"Cannot function!\n";return;}

void Instruction_mulTest::setUp()
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
  i = 0; // 20 * 10 = 200
  ret = mh->setValue((void*)&i,INT,"civar"); 
  CPPUNIT_ASSERT(!ret);

  d = 3.14;
  ret = mh->setValue((void*)&d,DOUBLE,"advar"); 
  CPPUNIT_ASSERT(!ret);
  d = 4.20; // 4.20 * 3.14 = 13.188
  ret = mh->setValue((void*)&d,DOUBLE,"bdvar"); 
  CPPUNIT_ASSERT(!ret);
  d = 0.0;
  ret = mh->setValue((void*)&d,DOUBLE,"cdvar"); 
  CPPUNIT_ASSERT(!ret);

  d = 3.03;
  ret = mh->setValue((void*)&d,DOUBLE,"apvar");
  CPPUNIT_ASSERT(!ret);
  p = Position(1.0,2.0);
  ret = mh->setValue((void*)&p,POSITION,"bpvar");
  CPPUNIT_ASSERT(!ret);
  p = Position(0,0); // (1,2) * 3.03  = (3.03, 6.06)
  ret = mh->setValue((void*)&p,POSITION,"cpvar");
  CPPUNIT_ASSERT(!ret);
}

void Instruction_mulTest::tearDown()
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

void Instruction_mulTest::testConstructor() {

  int ret;
  vector<string> args;

  args.clear(); // Correct int mul
  args.push_back("civar");
  args.push_back("bivar");
  args.push_back("aivar");
  i1 = new Instruction_mul(&ret, args);
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Correct double mul
  args.push_back("cdvar");
  args.push_back("bdvar");
  args.push_back("advar");
  i2 = new Instruction_mul(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Correct Position mul
  args.push_back("cpvar");
  args.push_back("bpvar");
  args.push_back("apvar");
  i3 = new Instruction_mul(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Wrong mul instruction . Will be detected at execute time
  args.push_back("cvar");
  args.push_back("bdvar");
  args.push_back("advar");
  i4 = new Instruction_mul(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Wrong mul instruction . Will be detected at execute time
  args.push_back("cpvar");
  args.push_back("bdvar");
  args.push_back("aivar");
  i5 = new Instruction_mul(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Wrong mul instruction . Will be detected at execute time
  args.push_back("aivar");
  args.push_back("aivar");
  args.push_back("advar");
  i6 = new Instruction_mul(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Wrong mul instruction. Detected here
  args.push_back("cvar");
  args.push_back("bdvar");
  i7 = new Instruction_mul(&ret, args);  
  CPPUNIT_ASSERT(ret);

}

void Instruction_mulTest::testExecute() {

  int ip;
  int iv;
  double dv;
  Position pv;

  int ret;
  vector<string> args;

  args.clear(); // Correct int mul
  args.push_back("civar");
  args.push_back("bivar");
  args.push_back("aivar");
  i1 = new Instruction_mul(&ret, args);
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Correct double mul
  args.push_back("cdvar");
  args.push_back("bdvar");
  args.push_back("advar");
  i2 = new Instruction_mul(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Correct Position mul
  args.push_back("cpvar");
  args.push_back("bpvar");
  args.push_back("apvar");
  i3 = new Instruction_mul(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Wrong mul instruction . Will be detected at execute time
  args.push_back("cvar");
  args.push_back("bdvar");
  args.push_back("advar");
  i4 = new Instruction_mul(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Wrong mul instruction . Will be detected at execute time
  args.push_back("cpvar");
  args.push_back("bdvar");
  args.push_back("aivar");
  i5 = new Instruction_mul(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Wrong mul instruction . Will be detected at execute time
  args.push_back("aivar");
  args.push_back("aivar");
  args.push_back("advar");
  i6 = new Instruction_mul(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Wrong mul instruction. Detected here
  args.push_back("cvar");
  args.push_back("bdvar");
  i7 = new Instruction_mul(&ret, args);  
  CPPUNIT_ASSERT(ret);

  CPPUNIT_ASSERT(!i1->execute(mh,&ip));
  CPPUNIT_ASSERT(!mh->getValue((void*)&iv,"civar"));
  CPPUNIT_ASSERT_EQUAL(iv, 200);

  CPPUNIT_ASSERT(!i2->execute(mh,&ip));
  CPPUNIT_ASSERT(!mh->getValue((void*)&dv,"cdvar"));
  CPPUNIT_ASSERT_EQUAL(dv, 13.188);

  CPPUNIT_ASSERT(!i3->execute(mh,&ip));
  CPPUNIT_ASSERT(!mh->getValue((void*)&pv,"cpvar"));
  CPPUNIT_ASSERT_EQUAL(pv.getX(), 3.03);
  CPPUNIT_ASSERT_EQUAL(pv.getY(), 6.06);

  CPPUNIT_ASSERT(i4->execute(mh,&ip));
  CPPUNIT_ASSERT(i5->execute(mh,&ip));
  CPPUNIT_ASSERT(i6->execute(mh,&ip));
  CPPUNIT_ASSERT(i7->execute(mh,&ip));
}

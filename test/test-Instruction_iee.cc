#include "test-Instruction_iee.h"
#include "ArgumentType.hh"
#include "MemoryHandler.hh"

#include <vector>
#include <string>
#include <iostream>

using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION( Instruction_ieeTest );

#define FAIL_ON(x) if(x) {cerr<<"Cannot function!\n";return;}

void Instruction_ieeTest::setUp()
{
	mh = new MemoryHandler();
  int i ;
  double d;
  int ret;

  // Integers for compare
  i = 5;
  ret = mh->setValue((void*)&i,INT,"i1"); 
  CPPUNIT_ASSERT(!ret);
  i = 7;
  ret = mh->setValue((void*)&i,INT,"i2"); 
  CPPUNIT_ASSERT(!ret);

  i = 5;
  ret = mh->setValue((void*)&i,INT,"i3"); 
  CPPUNIT_ASSERT(!ret);
  i = 5;
  ret = mh->setValue((void*)&i,INT,"i4"); 
  CPPUNIT_ASSERT(!ret);

  i = 7;
  ret = mh->setValue((void*)&i,INT,"i5"); 
  CPPUNIT_ASSERT(!ret);
  i = 5;
  ret = mh->setValue((void*)&i,INT,"i6"); 
  CPPUNIT_ASSERT(!ret);

  // Doubles for compare
  d = 20.0;
  ret = mh->setValue((void*)&d,DOUBLE,"d1"); 
  CPPUNIT_ASSERT(!ret);
  d = 30.00;
  ret = mh->setValue((void*)&d,DOUBLE,"d2"); 
  CPPUNIT_ASSERT(!ret);

  d = 20.0;
  ret = mh->setValue((void*)&d,DOUBLE,"d3"); 
  CPPUNIT_ASSERT(!ret);
  d = 19.99999999999999;
  ret = mh->setValue((void*)&d,DOUBLE,"d4"); 
  CPPUNIT_ASSERT(!ret);

  d = 0.4;
  ret = mh->setValue((void*)&d,DOUBLE,"d5"); 
  CPPUNIT_ASSERT(!ret);
  d = 0.2;
  ret = mh->setValue((void*)&d,DOUBLE,"d6"); 
  CPPUNIT_ASSERT(!ret);
}

void Instruction_ieeTest::tearDown()
{
	delete mh;
  delete i1;
  delete i2;
  delete i3;
  delete i4;
  delete i5;
  delete i6;
  delete i7;
  delete i8;
  delete i9;
  delete i10;
  delete i11;
}

void Instruction_ieeTest::testConstructor() {

  int ret;
  vector<string> args;

  args.clear(); // Correct int iee
  args.push_back("i1");
  args.push_back("i2");
  args.push_back("100");
  args.push_back("200");
  i1 = new Instruction_iee(&ret, args);
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Correct int iee
  args.push_back("i3");
  args.push_back("i4");
  args.push_back("100");
  args.push_back("200");
  i2 = new Instruction_iee(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Correct int iee
  args.push_back("i5");
  args.push_back("i6");
  args.push_back("100");
  args.push_back("200");
  i3 = new Instruction_iee(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Correct double iee
  args.push_back("d1");
  args.push_back("d2");
  args.push_back("100");
  args.push_back("200");
  i4 = new Instruction_iee(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Correct double iee
  args.push_back("d3");
  args.push_back("d4");
  args.push_back("100");
  args.push_back("200");
  i5 = new Instruction_iee(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Correct double iee
  args.push_back("d5");
  args.push_back("d6");
  args.push_back("100");
  args.push_back("200");
  i6 = new Instruction_iee(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Wrong iee instruction . Will be detected at execute time
  args.push_back("i1");
  args.push_back("d1000");
  args.push_back("100");
  args.push_back("200");
  i7 = new Instruction_iee(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Wrong iee instruction . Will be detected at execute time
  args.push_back("i1");
  args.push_back("asdfg");
  args.push_back("100");
  args.push_back("50");
  i8 = new Instruction_iee(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Wrong iee instruction . Will be detected at execute time
  args.push_back("i1");
  args.push_back("i211");
  args.push_back("2");
  args.push_back("200");
  i9 = new Instruction_iee(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Wrong iee instruction . Will be detected at execute time
  args.push_back("ab");
  args.push_back("d2");
  args.push_back("100");
  args.push_back("200");
  i10 = new Instruction_iee(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Wrong iee instruction. Detected here
  args.push_back("cvar");
  args.push_back("bdvar");
  args.push_back("100");
  i11 = new Instruction_iee(&ret, args);  
  CPPUNIT_ASSERT(ret);
}

void Instruction_ieeTest::testExecute() {

  int ip;

  int ret;
  vector<string> args;

  args.clear(); // Correct int iee
  args.push_back("i1");
  args.push_back("i2");
  args.push_back("100");
  args.push_back("200");
  i1 = new Instruction_iee(&ret, args);
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Correct int iee
  args.push_back("i3");
  args.push_back("i4");
  args.push_back("100");
  args.push_back("200");
  i2 = new Instruction_iee(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Correct int iee
  args.push_back("i5");
  args.push_back("i6");
  args.push_back("100");
  args.push_back("200");
  i3 = new Instruction_iee(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Correct double iee
  args.push_back("d1");
  args.push_back("d2");
  args.push_back("100");
  args.push_back("200");
  i4 = new Instruction_iee(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Correct double iee
  args.push_back("d3");
  args.push_back("d4");
  args.push_back("100");
  args.push_back("200");
  i5 = new Instruction_iee(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Correct double iee
  args.push_back("d5");
  args.push_back("d6");
  args.push_back("100");
  args.push_back("200");
  i6 = new Instruction_iee(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Wrong iee instruction . Will be detected at execute time
  args.push_back("i1");
  args.push_back("d1000");
  args.push_back("100");
  args.push_back("200");
  i7 = new Instruction_iee(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Wrong iee instruction . Will be detected at execute time
  args.push_back("i1");
  args.push_back("asdfg");
  args.push_back("100");
  args.push_back("50");
  i8 = new Instruction_iee(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Wrong iee instruction . Will be detected at execute time
  args.push_back("i1");
  args.push_back("i211");
  args.push_back("2");
  args.push_back("200");
  i9 = new Instruction_iee(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Wrong iee instruction . Will be detected at execute time
  args.push_back("ab");
  args.push_back("d2");
  args.push_back("100");
  args.push_back("200");
  i10 = new Instruction_iee(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Wrong iee instruction. Detected here
  args.push_back("cvar");
  args.push_back("bdvar");
  args.push_back("100");
  i11 = new Instruction_iee(&ret, args);  
  CPPUNIT_ASSERT(ret);

  ip = 0;
  CPPUNIT_ASSERT(!i1->execute(mh,&ip));
  CPPUNIT_ASSERT_EQUAL(200, ip);

  ip = 0;
  CPPUNIT_ASSERT(!i2->execute(mh,&ip));
  CPPUNIT_ASSERT_EQUAL(100, ip);

  ip = 0;
  CPPUNIT_ASSERT(!i3->execute(mh,&ip));
  CPPUNIT_ASSERT_EQUAL(200, ip);

  ip = 0;
  CPPUNIT_ASSERT(!i4->execute(mh,&ip));
  CPPUNIT_ASSERT_EQUAL(200, ip);

  ip = 0;
  CPPUNIT_ASSERT(!i5->execute(mh,&ip));
  CPPUNIT_ASSERT_EQUAL(100, ip);

  ip = 0;
  CPPUNIT_ASSERT(!i6->execute(mh,&ip));
  CPPUNIT_ASSERT_EQUAL(200, ip);

  CPPUNIT_ASSERT(i7->execute(mh,&ip));
  CPPUNIT_ASSERT(i8->execute(mh,&ip));
  CPPUNIT_ASSERT(i9->execute(mh,&ip));
  CPPUNIT_ASSERT(i10->execute(mh,&ip));
}

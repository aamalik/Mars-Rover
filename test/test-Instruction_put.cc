#include "test-Instruction_put.h"
#include "ArgumentType.hh"
#include "MemoryHandler.hh"

#include <vector>
#include <string>
#include <iostream>

using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION( Instruction_putTest );

#define FAIL_ON(x) if(x) {cerr<<"Cannot function!\n";return;}

void Instruction_putTest::setUp()
{
	mh = new MemoryHandler();
  int i;
  double d;
  Position p;
  string s;
  int ret;

  // Int Values to put
  i = 0;
  ret = mh->setValue((void*)&i,INT,"i1"); 
  CPPUNIT_ASSERT(!ret);
  i = 1;
  ret = mh->setValue((void*)&i,INT,"i2"); 
  CPPUNIT_ASSERT(!ret);

  // Double Values to put
  d = 0.0;
  ret = mh->setValue((void*)&d,DOUBLE,"d1"); 
  CPPUNIT_ASSERT(!ret);
  d = 1.5;
  ret = mh->setValue((void*)&d,DOUBLE,"d2"); 
  CPPUNIT_ASSERT(!ret);

  // Position Values to put
  p.setX(0.0);
  p.setY(0.0);
  ret = mh->setValue((void*)&p,POSITION,"p1"); 
  CPPUNIT_ASSERT(!ret);
  p.setX(2.0);
  p.setY(3.0);
  ret = mh->setValue((void*)&p,POSITION,"p2"); 
  CPPUNIT_ASSERT(!ret);

  // String Values to put
  s = "";
  ret = mh->setValue((void*)&s,STRING,"s1"); 
  CPPUNIT_ASSERT(!ret);
  s = "goright";
  ret = mh->setValue((void*)&s,STRING,"s2"); 
  CPPUNIT_ASSERT(!ret);
}

void Instruction_putTest::tearDown()
{
	delete mh;
  delete i1;
  delete i2;
  delete i3;
  delete i4;
  delete i5;
  delete i6;
}

void Instruction_putTest::testConstructor() {

  int ret;
  vector<string> args;

  args.clear(); // Correct put
  args.push_back("i1");
  args.push_back("i2");
  i1 = new Instruction_put(&ret, args);
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Correct put
  args.push_back("d1");
  args.push_back("d2");
  i2 = new Instruction_put(&ret, args);
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Correct put
  args.push_back("p1");
  args.push_back("p2");
  i3 = new Instruction_put(&ret, args);
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Correct put
  args.push_back("s1");
  args.push_back("s2");
  i4 = new Instruction_put(&ret, args);
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Wrong put instruction . Will be detected at execute time
  args.push_back("i1");
  args.push_back("d2");
  i5 = new Instruction_put(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Wrong put instruction. Detected here
  args.push_back("pos1");
  i6 = new Instruction_put(&ret, args);  
  CPPUNIT_ASSERT(ret);
}

void Instruction_putTest::testExecute() {

  int ip;
  int iv;
  double dv;
  Position pv;
  string sv;
  int ret;
  vector<string> args;

  args.clear(); // Correct put
  args.push_back("i1");
  args.push_back("i2");
  i1 = new Instruction_put(&ret, args);
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Correct put
  args.push_back("d1");
  args.push_back("d2");
  i2 = new Instruction_put(&ret, args);
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Correct put
  args.push_back("p1");
  args.push_back("p2");
  i3 = new Instruction_put(&ret, args);
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Correct put
  args.push_back("s1");
  args.push_back("s2");
  i4 = new Instruction_put(&ret, args);
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Wrong put instruction . Will be detected at execute time
  args.push_back("i1");
  args.push_back("d2");
  i5 = new Instruction_put(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Wrong put instruction. Detected here
  args.push_back("pos1");
  i6 = new Instruction_put(&ret, args);  
  CPPUNIT_ASSERT(ret);

  CPPUNIT_ASSERT(!i1->execute(mh,&ip));
  CPPUNIT_ASSERT(!mh->getValue((void*)&iv,"i1"));
  CPPUNIT_ASSERT_EQUAL(iv, 1);

  CPPUNIT_ASSERT(!i2->execute(mh,&ip));
  CPPUNIT_ASSERT(!mh->getValue((void*)&dv,"d1"));
  CPPUNIT_ASSERT_EQUAL(dv, 1.5);

  CPPUNIT_ASSERT(!i3->execute(mh,&ip));
  CPPUNIT_ASSERT(!mh->getValue((void*)&pv,"p1"));
  CPPUNIT_ASSERT_EQUAL(pv.getX(), 2.0);
  CPPUNIT_ASSERT_EQUAL(pv.getY(), 3.0);

  CPPUNIT_ASSERT(!i4->execute(mh,&ip));
  CPPUNIT_ASSERT(!mh->getValue((void*)&sv,"s1"));
  CPPUNIT_ASSERT( sv == "goright" );

  CPPUNIT_ASSERT(i5->execute(mh,&ip));
}

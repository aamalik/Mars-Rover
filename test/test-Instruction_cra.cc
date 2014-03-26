#include "test-Instruction_cra.h"
#include "ArgumentType.hh"
#include "MemoryHandler.hh"

#include <vector>
#include <string>
#include <iostream>

using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION( Instruction_craTest );

#define FAIL_ON(x) if(x) {cerr<<"Cannot function!\n";return;}

void Instruction_craTest::setUp()
{
	mh = new MemoryHandler();

}

void Instruction_craTest::tearDown()
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

void Instruction_craTest::testConstructor() {

  int ret;
  vector<string> args;

  args.clear(); // Correct int cra
  args.push_back("*Int");
  args.push_back("2");
  args.push_back("*ia");
  i1 = new Instruction_cra(&ret, args);
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Correct double cra
  args.push_back("*Double");
  args.push_back("10");
  args.push_back("*da");
  i2 = new Instruction_cra(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Correct Position cra
  args.push_back("*Position");
  args.push_back("5");
  args.push_back("*pa");
  i3 = new Instruction_cra(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Correct String cra
  args.push_back("*String");
  args.push_back("2");
  args.push_back("*sa");
  i4 = new Instruction_cra(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Wrong cra instruction . Detected here
  args.push_back("*Int");
  args.push_back("100000");
  args.push_back("*ia");
  i5 = new Instruction_cra(&ret, args);  
  CPPUNIT_ASSERT(ret);

  args.clear(); // Wrong cra instruction . Detected here
  args.push_back("*String");
  args.push_back("-10");
  args.push_back("*sa");
  i6 = new Instruction_cra(&ret, args);  
  CPPUNIT_ASSERT(ret);

  args.clear(); // Wrong cra instruction. Detected here
  args.push_back("x");
  i7 = new Instruction_cra(&ret, args);  
  CPPUNIT_ASSERT(ret);
}

void Instruction_craTest::testExecute() {

  int ip;
  int iv;
  double dv;
  Position pv;
  string sv;
  ArgumentType t = NOTYPE;

  int ret;
  vector<string> args;

  args.clear(); // Correct int cra
  args.push_back("*Int");
  args.push_back("2");
  args.push_back("*ia");
  i1 = new Instruction_cra(&ret, args);
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Correct double cra
  args.push_back("*Double");
  args.push_back("10");
  args.push_back("*da");
  i2 = new Instruction_cra(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Correct Position cra
  args.push_back("*Position");
  args.push_back("5");
  args.push_back("*pa");
  i3 = new Instruction_cra(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Correct String cra
  args.push_back("*String");
  args.push_back("2");
  args.push_back("*sa");
  i4 = new Instruction_cra(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Wrong cra instruction . Detected here
  args.push_back("*Int");
  args.push_back("100000");
  args.push_back("*ia");
  i5 = new Instruction_cra(&ret, args);  
  CPPUNIT_ASSERT(ret);

  args.clear(); // Wrong cra instruction . Detected here
  args.push_back("*String");
  args.push_back("-10");
  args.push_back("*sa");
  i6 = new Instruction_cra(&ret, args);  
  CPPUNIT_ASSERT(ret);

  args.clear(); // Wrong cra instruction. Detected here
  args.push_back("x");
  i7 = new Instruction_cra(&ret, args);  
  CPPUNIT_ASSERT(ret);

  CPPUNIT_ASSERT(!i1->execute(mh,&ip));
  CPPUNIT_ASSERT(!mh->getType(&t,"ia"));
  CPPUNIT_ASSERT( t == INTARRAY );
  CPPUNIT_ASSERT(!mh->getType(&t,"ia[0]"));
  CPPUNIT_ASSERT( t == INT );
  CPPUNIT_ASSERT(!mh->getType(&t,"ia[1]"));
  CPPUNIT_ASSERT( t == INT );
  CPPUNIT_ASSERT(mh->getType(&t,"ia[2]"));
  CPPUNIT_ASSERT(mh->getType(&t,"ia[-1]"));
  CPPUNIT_ASSERT(!mh->getValue((void*)&iv,"ia[0]"));
  CPPUNIT_ASSERT_EQUAL(iv, 0);

  // Some array set test JUST FOR FUN
  iv = 10;
  CPPUNIT_ASSERT(!mh->setValue((void*)&iv,INT,"ia[0]"));
  iv = 20;
  CPPUNIT_ASSERT(!mh->setValue((void*)&iv,INT,"ia[1]"));
  CPPUNIT_ASSERT(!mh->getValue((void*)&iv,"ia[0]"));
  CPPUNIT_ASSERT_EQUAL(iv, 10);
  CPPUNIT_ASSERT(!mh->getValue((void*)&iv,"ia[1]"));
  CPPUNIT_ASSERT_EQUAL(iv, 20);

  CPPUNIT_ASSERT(!i2->execute(mh,&ip));
  CPPUNIT_ASSERT(!mh->getType(&t,"da"));
  CPPUNIT_ASSERT( t == DOUBLEARRAY );
  CPPUNIT_ASSERT(!mh->getType(&t,"da[0]"));
  CPPUNIT_ASSERT( t == DOUBLE );
  CPPUNIT_ASSERT(!mh->getType(&t,"da[5]"));
  CPPUNIT_ASSERT( t == DOUBLE );
  CPPUNIT_ASSERT(!mh->getType(&t,"da[9]"));
  CPPUNIT_ASSERT( t == DOUBLE );
  CPPUNIT_ASSERT(mh->getType(&t,"da[10]"));
  CPPUNIT_ASSERT(mh->getType(&t,"da[-1]"));
  CPPUNIT_ASSERT(!mh->getValue((void*)&dv,"da[0]"));
  CPPUNIT_ASSERT_EQUAL(dv, 0.0);
  CPPUNIT_ASSERT(!mh->getValue((void*)&dv,"da[7]"));
  CPPUNIT_ASSERT_EQUAL(dv, 0.0);

  CPPUNIT_ASSERT(!i3->execute(mh,&ip));
  CPPUNIT_ASSERT(!mh->getType(&t,"pa"));
  CPPUNIT_ASSERT( t == POSITIONARRAY );
  CPPUNIT_ASSERT(!mh->getType(&t,"pa[0]"));
  CPPUNIT_ASSERT( t == POSITION );
  CPPUNIT_ASSERT(!mh->getType(&t,"pa[2]"));
  CPPUNIT_ASSERT( t == POSITION );
  CPPUNIT_ASSERT(!mh->getType(&t,"pa[4]"));
  CPPUNIT_ASSERT( t == POSITION );
  CPPUNIT_ASSERT(mh->getType(&t,"pa[5]"));
  CPPUNIT_ASSERT(mh->getType(&t,"pa[-1]"));
  CPPUNIT_ASSERT(!mh->getValue((void*)&pv,"pa[0]"));
  CPPUNIT_ASSERT_EQUAL(pv.getX(), 0.0);
  CPPUNIT_ASSERT_EQUAL(pv.getY(), 0.0);
  CPPUNIT_ASSERT(!mh->getValue((void*)&pv,"pa[3]"));
  CPPUNIT_ASSERT_EQUAL(pv.getX(), 0.0);
  CPPUNIT_ASSERT_EQUAL(pv.getY(), 0.0);

  CPPUNIT_ASSERT(!i4->execute(mh,&ip));
  CPPUNIT_ASSERT(!mh->getType(&t,"sa"));
  CPPUNIT_ASSERT( t == STRINGARRAY );
  CPPUNIT_ASSERT(!mh->getType(&t,"sa[0]"));
  CPPUNIT_ASSERT( t == STRING );
  CPPUNIT_ASSERT(!mh->getType(&t,"sa[1]"));
  CPPUNIT_ASSERT( t == STRING );
  CPPUNIT_ASSERT(mh->getType(&t,"sa[5]"));
  CPPUNIT_ASSERT(mh->getType(&t,"sa[-2]"));
  CPPUNIT_ASSERT(!mh->getValue((void*)&sv,"sa[0]"));
  CPPUNIT_ASSERT(sv == "");

}

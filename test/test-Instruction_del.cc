#include "test-Instruction_del.h"
#include "ArgumentType.hh"
#include "MemoryHandler.hh"

#include <vector>
#include <string>
#include <iostream>

using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION( Instruction_delTest );

#define FAIL_ON(x) if(x) {cerr<<"Cannot function!\n";return;}

void Instruction_delTest::setUp()
{
	mh = new MemoryHandler();
  int i;
  double d;
  Position p;
  string s;
  int ret;

  i=1;
  ret = mh->setValue((void*)&i,INT,"ivar"); 
  CPPUNIT_ASSERT(!ret);
  d = 2.0;
  ret = mh->setValue((void*)&d,DOUBLE,"dvar"); 
  CPPUNIT_ASSERT(!ret);
  p.setX(3.0);
  p.setY(4.0);
  ret = mh->setValue((void*)&p,POSITION,"pvar"); 
  CPPUNIT_ASSERT(!ret);
  s = "STRING";
  ret = mh->setValue((void*)&s,STRING,"svar"); 
  CPPUNIT_ASSERT(!ret);

  ret = mh->setValue(NULL,INT,"ia:5"); 
  CPPUNIT_ASSERT(!ret);
  ret = mh->setValue(NULL,DOUBLE,"da:5"); 
  CPPUNIT_ASSERT(!ret);
  ret = mh->setValue(NULL,POSITION,"pa:5"); 
  CPPUNIT_ASSERT(!ret);
  ret = mh->setValue(NULL,STRING,"sa:5"); 
  CPPUNIT_ASSERT(!ret);
}

void Instruction_delTest::tearDown()
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
}

void Instruction_delTest::testConstructor() {

  int ret;
  vector<string> args;

  args.clear(); // Correct int del
  args.push_back("*ivar");
  i1 = new Instruction_del(&ret, args);
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Correct double del
  args.push_back("*dvar");
  i2 = new Instruction_del(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Correct Position del
  args.push_back("*pvar");
  i3 = new Instruction_del(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Correct String del
  args.push_back("*svar");
  i4 = new Instruction_del(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Correct int array del
  args.push_back("*ia");
  i5 = new Instruction_del(&ret, args);
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Correct double array del
  args.push_back("*da");
  i6 = new Instruction_del(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Correct Position array del
  args.push_back("*pa");
  i7 = new Instruction_del(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Correct String array del
  args.push_back("*sa");
  i8 = new Instruction_del(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Wrong del instruction . Will be detected at execute time
  args.push_back("*MapLength");
  i9 = new Instruction_del(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Wrong del instruction. Detected here
  i10 = new Instruction_del(&ret, args);  
  CPPUNIT_ASSERT(ret);
}

void Instruction_delTest::testExecute() {

  int ip;
  ArgumentType t = NOTYPE;

  int ret;
  vector<string> args;

  args.clear(); // Correct int del
  args.push_back("*ivar");
  i1 = new Instruction_del(&ret, args);
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Correct double del
  args.push_back("*dvar");
  i2 = new Instruction_del(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Correct Position del
  args.push_back("*pvar");
  i3 = new Instruction_del(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Correct String del
  args.push_back("*svar");
  i4 = new Instruction_del(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Correct int array del
  args.push_back("*ia");
  i5 = new Instruction_del(&ret, args);
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Correct double array del
  args.push_back("*da");
  i6 = new Instruction_del(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Correct Position array del
  args.push_back("*pa");
  i7 = new Instruction_del(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Correct String array del
  args.push_back("*sa");
  i8 = new Instruction_del(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Wrong del instruction . Will be detected at execute time
  args.push_back("*MapLength");
  i9 = new Instruction_del(&ret, args);  
  CPPUNIT_ASSERT(!ret);

  args.clear(); // Wrong del instruction. Detected here
  i10 = new Instruction_del(&ret, args);  
  CPPUNIT_ASSERT(ret);

  CPPUNIT_ASSERT(!mh->getType(&t,"ivar"));
  CPPUNIT_ASSERT(!i1->execute(mh,&ip));
  CPPUNIT_ASSERT(mh->getType(&t,"ivar"));

  CPPUNIT_ASSERT(!mh->getType(&t,"dvar"));
  CPPUNIT_ASSERT(!i2->execute(mh,&ip));
  CPPUNIT_ASSERT(mh->getType(&t,"dvar"));

  CPPUNIT_ASSERT(!mh->getType(&t,"pvar"));
  CPPUNIT_ASSERT(!i3->execute(mh,&ip));
  CPPUNIT_ASSERT(mh->getType(&t,"pvar"));

  CPPUNIT_ASSERT(!mh->getType(&t,"svar"));
  CPPUNIT_ASSERT(!i4->execute(mh,&ip));
  CPPUNIT_ASSERT(mh->getType(&t,"svar"));

  CPPUNIT_ASSERT(!mh->getType(&t,"ia"));
  CPPUNIT_ASSERT(!i5->execute(mh,&ip));
  CPPUNIT_ASSERT(mh->getType(&t,"ia"));

  CPPUNIT_ASSERT(!mh->getType(&t,"da"));
  CPPUNIT_ASSERT(!i6->execute(mh,&ip));
  CPPUNIT_ASSERT(mh->getType(&t,"da"));

  CPPUNIT_ASSERT(!mh->getType(&t,"pa"));
  CPPUNIT_ASSERT(!i7->execute(mh,&ip));
  CPPUNIT_ASSERT(mh->getType(&t,"pa"));

  CPPUNIT_ASSERT(!mh->getType(&t,"sa"));
  CPPUNIT_ASSERT(!i8->execute(mh,&ip));
  CPPUNIT_ASSERT(mh->getType(&t,"sa"));

  CPPUNIT_ASSERT(i9->execute(mh,&ip));
}

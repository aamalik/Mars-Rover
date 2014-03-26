#include "test-VariableRegister.h"
#include "ArgumentType.hh"

CPPUNIT_TEST_SUITE_REGISTRATION( VariableRegisterTest );

void VariableRegisterTest::setUp()
{
  int intVal = 3;
  string stringVal("test123");

  vr1 = new VariableRegister();

  vr1->setValue(&intVal, INT, "SampleInt");
  vr1->setValue(&intVal, INT, "IntDeleteTestVal");

  vr1->setValue(&stringVal, STRING, "SampleString");
  vr1->setValue(&stringVal, STRING, "StringDeleteTestVal");
  

}

void VariableRegisterTest::tearDown()
{
  delete vr1;
}

void VariableRegisterTest::testConstructor() {
  // Process
  int time=2, ret;
  ret = vr1->getValue(&time, "SomeValue");

  // Check
  CPPUNIT_ASSERT( ret != 0 );
  CPPUNIT_ASSERT_EQUAL(2, time);
}

void VariableRegisterTest::testGetType() {
  ArgumentType type;
  int ret;
  int ival = 4;
  double dval = 3.0;
  string sval("123");

  //testing int
  ret = vr1->setValue(&ival, INT, "SomeInt");
  CPPUNIT_ASSERT_EQUAL(0, ret);
  ret = vr1->getType(&type, "SomeInt");
  CPPUNIT_ASSERT_EQUAL(INT, type);
  CPPUNIT_ASSERT_EQUAL(0, ret);

  //testing double
  ret = vr1->setValue(&dval, DOUBLE, "SomeDouble");
  CPPUNIT_ASSERT_EQUAL(0, ret);
  ret = vr1->getType(&type, "SomeDouble");
  CPPUNIT_ASSERT_EQUAL(DOUBLE, type);
  CPPUNIT_ASSERT_EQUAL(0, ret);

  //testing string
  ret = vr1->setValue(&sval, STRING, "SomeString");
  CPPUNIT_ASSERT_EQUAL(0, ret);
  ret = vr1->getType(&type, "SomeString");
  CPPUNIT_ASSERT_EQUAL(STRING, type);
  CPPUNIT_ASSERT_EQUAL(0, ret);
}

void VariableRegisterTest::testDeleteValue() {
  int ret, dummyInt;
  ret = vr1->deleteValue("NoSuchValue");
  CPPUNIT_ASSERT(ret != 0);

  ret = vr1->deleteValue("IntDeleteTestVal");
  CPPUNIT_ASSERT_EQUAL(0, ret);

  ret = vr1->getValue(&dummyInt, "IntDeleteTestVal");
  CPPUNIT_ASSERT(ret != 0);
}

void VariableRegisterTest::testSetValue() {
  int ret;

  //test setting an int variable
  int ei = 1;
  ret = vr1->setValue(&ei, INT, "MyInt");
  CPPUNIT_ASSERT_EQUAL(0, ret);
  CPPUNIT_ASSERT_EQUAL(1, vr1->intMap["MyInt"]);

  //test setting an double variable
  double ed = 1;
  ret = vr1->setValue(&ed, INT, "MyDouble");
  CPPUNIT_ASSERT_EQUAL(0, ret);
  //CPPUNIT_ASSERT_DOUBLE_EQUAL(1.0, vr1->doubleMap["MyDouble"], 0.001);

  //test setting a string variable
  string es("Hello I'm a string");
  ret = vr1->setValue(&es, STRING, "MyString");
  CPPUNIT_ASSERT_EQUAL(0, ret);
  CPPUNIT_ASSERT_EQUAL(es, vr1->stringMap["MyString"]);

  //test setting a Position variable
  Position pos(2, 3);
  ret = vr1->setValue(&pos, POSITION, "MyPos");
  CPPUNIT_ASSERT_EQUAL(0, ret);
  CPPUNIT_ASSERT(pos == vr1->positionMap["MyPos"]);
}

void VariableRegisterTest::testGetValue() {
  int ret;
  int intValOut = -1;
  string stringValOut, stringValExp("test123");

  //test getting a non-existent variable
  ret = vr1->getValue(&intValOut, "NoSuchVariable");
  CPPUNIT_ASSERT(ret != 0);

  //test getting an int variable
  ret = vr1->getValue(&intValOut, "SampleInt");
  CPPUNIT_ASSERT_EQUAL(0, ret);
  CPPUNIT_ASSERT_EQUAL(3, intValOut);

  //test getting an int variable
  ret = vr1->getValue(&stringValOut, "SampleString");
  CPPUNIT_ASSERT_EQUAL(0, ret);
  CPPUNIT_ASSERT_EQUAL(stringValExp, stringValOut);
}

void VariableRegisterTest::testClean() {
  int ret, dummyInt=-1;
  string dummyString("");

  vr1->clean();

  ret = vr1->getValue(&dummyInt, "SampleInt");
  CPPUNIT_ASSERT(ret != 0);
  CPPUNIT_ASSERT_EQUAL(-1, dummyInt);

  ret = vr1->getValue(&dummyString, "SampleString");
  CPPUNIT_ASSERT(ret != 0);
}

void VariableRegisterTest::testExistsValue() {
  bool ret;
  int i=1;
  vr1->setValue(&i, INT, "SampleInt");
  //test existing variables
  ret = vr1->existsValue("SampleInt");
  CPPUNIT_ASSERT_EQUAL(true, ret);

  //test non-existing variable
  ret = vr1->existsValue("NoSuchVariable");
  CPPUNIT_ASSERT_EQUAL(false, ret);
}
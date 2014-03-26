#include "test-SpaceObjectRegister.h"
#include "ArgumentType.hh"

CPPUNIT_TEST_SUITE_REGISTRATION( SpaceObjectRegisterTest );

void SpaceObjectRegisterTest::setUp()
{
  obj1 = new SpaceObject(1, 1, 1, 0, 0);
  obj2 = new SpaceObject(2, 2, 2, 0, 0);
  obj3 = new SpaceObject(3, 3, 3, 0, 0); 
  //obj4 = new SpaceObject(4, 4, 4, 0, 0); 
  martian1 = new SpaceObject(1, 1, 0.5, 1 ,1);
  martian2 = new SpaceObject(2, 2, 0.5, 2 ,2);
  martian3 = new SpaceObject(3, 3, 0.5, 3 ,3);
  //martian4 = new SpaceObject(4, 4, 0.5, 4 ,4);
  int im1 = -1, i0 = 0, i1 = 1, i2 = 2, i3 = 3, i4 = 4, i5 = 5;
  vr1 = new VariableRegister();
	mr1 = new SpaceObjectRegister(vr1);
  vr1->setValue(&im1, INT, "im1");
  vr1->setValue(&i0, INT, "i0");
  vr1->setValue(&i1, INT, "i1");
  vr1->setValue(&i2, INT, "i2");
  vr1->setValue(&i3, INT, "i3");
  vr1->setValue(&i4, INT, "i4");
  vr1->setValue(&i5, INT, "i5");
  mr1->Boulders.push_back(*obj1);
  mr1->Boulders.push_back(*obj2);
  mr1->Boulders.push_back(*obj3);
  mr1->Craters.push_back(*obj1);
  mr1->Craters.push_back(*obj2);
  mr1->Craters.push_back(*obj3);
  mr1->Martians.push_back(*martian1);
  mr1->Martians.push_back(*martian2);
  mr1->Martians.push_back(*martian3);
}

void SpaceObjectRegisterTest::tearDown()
{
	delete mr1;
  delete vr1;

  delete obj1;
  delete obj2;
  delete obj3 ;
  //delete obj4;
  delete martian1;
  delete martian2;
  delete martian3;
  //delete martian4;
}

void SpaceObjectRegisterTest::testContainsObject() {
  SpaceObject so1(0, 0, 0, 0, 0);
  SpaceObject so2(1, 2, 3, 4, 5);
  SpaceObject so3(2, 3, 4, 5, 6);
  SpaceObject so4(3, 4, 5, 6, 7);
  SpaceObject so5(4, 5, 6, 7, 8);
  SpaceObject so6(5, 6, 7, 8, 9);
  SpaceObject so7(0, 6, 7, 8, 0);

  CPPUNIT_ASSERT(!mr1->containsObject(&so1));
  mr1->Boulders.push_back(so1);
  CPPUNIT_ASSERT(mr1->containsObject(&so1));
  mr1->Boulders.push_back(so2);
  CPPUNIT_ASSERT(mr1->containsObject(&so2));
  mr1->Craters.push_back(so3);
  CPPUNIT_ASSERT(mr1->containsObject(&so3));
  mr1->Craters.push_back(so4);
  CPPUNIT_ASSERT(mr1->containsObject(&so4));
  mr1->Martians.push_back(so5);
  CPPUNIT_ASSERT(mr1->containsObject(&so5));
  mr1->Martians.push_back(so6);
  CPPUNIT_ASSERT(mr1->containsObject(&so6));

  CPPUNIT_ASSERT(!mr1->containsObject(&so7));
}

void SpaceObjectRegisterTest::testParseSpaceObjects() {
	int ret;
	//good init string
  //data1:
	std::string data1 = "b 1.000 2.000 3.000;";
  SpaceObject b_1_2_3(1, 2, 3, 0, 0);

	std::string data2 = "m 1.000 2.000 3.000 4.000;";
  SpaceObject m_1_2_3_4(1, 2, 0.5, 3, 4);
	std::string data3 = "b 2.000 3.000 4.000 c 1.500 2.5000 3.000 m 1.000 3.000 5.000 7.000 b 9.000 8.000 7.000;";
  SpaceObject b_2_3_4(2, 3, 4, 0, 0), c_1p5_2p5_3(1.5, 2.5, 3, 0, 0), m_1_3_5_7(1, 3, 0.5, 5, 7), b_9_8_7(9, 8, 7, 0, 0);

	//bad init strings
	std::string data4 = "b 100.00 101.000;"; //too few
  std::string data5 = "b 100.00 101.000 1.000"; //missing semicolon
  std::string data6 = "b 1.000 2.000 3.000 4.000 m 2.000 3.000 4.000 5.000;"; //to many args for boulder
  

	ret = mr1->parseSpaceObjects(data1);
  CPPUNIT_ASSERT_EQUAL(0, ret);
  CPPUNIT_ASSERT(mr1->containsObject(&b_1_2_3));

  ret = mr1->parseSpaceObjects(data2);
  CPPUNIT_ASSERT_EQUAL(0, ret);
  CPPUNIT_ASSERT(mr1->containsObject(&m_1_2_3_4));

  ret = mr1->parseSpaceObjects(data3);
  CPPUNIT_ASSERT_EQUAL(0, ret);
  CPPUNIT_ASSERT(mr1->containsObject(&b_2_3_4));
  CPPUNIT_ASSERT(mr1->containsObject(&b_9_8_7));
  CPPUNIT_ASSERT(mr1->containsObject(&c_1p5_2p5_3));
  CPPUNIT_ASSERT(mr1->containsObject(&m_1_3_5_7));
	
	
	ret = mr1->parseSpaceObjects(data4); 
	CPPUNIT_ASSERT(ret != 0);
	ret = mr1->parseSpaceObjects(data5); 
	CPPUNIT_ASSERT(ret != 0);
	ret = mr1->parseSpaceObjects(data6); 
	CPPUNIT_ASSERT(ret != 0);
}

void SpaceObjectRegisterTest::testGetType() {
    ArgumentType type;
    int ret;

    //testing getting a general boulder.
    //this part also includes the array bounds tests
    ret = mr1->getType(&type, "Boulder[i0]"); //min index
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_EQUAL(BOULDER, type);
    ret = mr1->getType(&type, "Boulder[i2]"); //max index
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_EQUAL(BOULDER, type);
    ret = mr1->getType(&type, "Boulder[i3]"); //out of bounds +1
    CPPUNIT_ASSERT(0 != ret);
    ret = mr1->getType(&type, "Boulder[im1]"); //out of bounds -1
    CPPUNIT_ASSERT(0 != ret);
    ret = mr1->getType(&type, "Boulder[j0]"); //non existent index
    CPPUNIT_ASSERT(0 != ret);

    //testing getting a general Crater.
    //this part also includes the array bounds tests
    ret = mr1->getType(&type, "Crater[i0]"); //min index
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_EQUAL(CRATER, type);
    ret = mr1->getType(&type, "Crater[i2]"); //max index
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_EQUAL(CRATER, type);
    ret = mr1->getType(&type, "Crater[i3]"); //out of bounds +1
    CPPUNIT_ASSERT(0 != ret);
    ret = mr1->getType(&type, "Crater[im1]"); //out of bounds -1
    CPPUNIT_ASSERT(0 != ret);
    ret = mr1->getType(&type, "Crater[j0]"); //non existent index
    CPPUNIT_ASSERT(0 != ret);

    //testing getting a general Martian.
    //this part also includes the array bounds tests
    ret = mr1->getType(&type, "Martian[i0]"); //min index
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_EQUAL(MARTIAN, type);
    ret = mr1->getType(&type, "Martian[i2]"); //max index
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_EQUAL(MARTIAN, type);
    ret = mr1->getType(&type, "Martian[i3]"); //out of bounds +1
    CPPUNIT_ASSERT(0 != ret);
    ret = mr1->getType(&type, "Martian[im1]"); //out of bounds -1
    CPPUNIT_ASSERT(0 != ret);
    ret = mr1->getType(&type, "Martian[j0]"); //non existent index
    CPPUNIT_ASSERT(0 != ret);


    // Testing the individial elements on one example (indexes were )
    
    //testing the boulders elements
    ret = mr1->getType(&type, "Boulder[i0].Position"); 
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_EQUAL(POSITION, type);
    ret = mr1->getType(&type, "Boulder[i0].Radius"); 
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_EQUAL(DOUBLE, type);
    ret = mr1->getType(&type, "Boulder[i0].X"); 
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_EQUAL(DOUBLE, type);
    ret = mr1->getType(&type, "Boulder[i0].Y"); 
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_EQUAL(DOUBLE, type);

    //testing the Crater elements
    ret = mr1->getType(&type, "Crater[i0].Position"); 
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_EQUAL(POSITION, type);
    ret = mr1->getType(&type, "Crater[i0].Radius"); 
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_EQUAL(DOUBLE, type);
    ret = mr1->getType(&type, "Crater[i0].X"); 
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_EQUAL(DOUBLE, type);
    ret = mr1->getType(&type, "Crater[i0].Y"); 
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_EQUAL(DOUBLE, type);

    //testing the Martian elements
    ret = mr1->getType(&type, "Martian[i0].Position"); 
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_EQUAL(POSITION, type);
    ret = mr1->getType(&type, "Martian[i0].Radius"); 
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_EQUAL(DOUBLE, type);
    ret = mr1->getType(&type, "Martian[i0].X"); 
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_EQUAL(DOUBLE, type);
    ret = mr1->getType(&type, "Martian[i0].Y"); 
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_EQUAL(DOUBLE, type);
    ret = mr1->getType(&type, "Martian[i0].Speed"); 
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_EQUAL(DOUBLE, type);
    ret = mr1->getType(&type, "Martian[i0].Heading"); 
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_EQUAL(DOUBLE, type);
  }

  void SpaceObjectRegisterTest::testGetValue() {
    int ret;

    SpaceObject so(0, 0, 0, 0, 0);
    double x, y, radius, speed, heading;
    Position pos(0, 0);

    //testing getting a general boulder.
    //this part also includes the array bounds tests
    ret = mr1->getValue(&so, "Boulder[i0]"); //min index
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT(*obj1 == so);
    ret = mr1->getValue(&so, "Boulder[i2]"); //max index
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT(*obj3 == so);
    ret = mr1->getValue(&so, "Boulder[i3]"); //out of bounds +1
    CPPUNIT_ASSERT(0 != ret);
    ret = mr1->getValue(&so, "Boulder[im1]"); //out of bounds -1
    CPPUNIT_ASSERT(0 != ret);
    ret = mr1->getValue(&so, "Boulder[j0]"); //non existent index
    CPPUNIT_ASSERT(0 != ret);

    //testing getting a general Crater.
    //this part also includes the array bounds tests
    ret = mr1->getValue(&so, "Crater[i0]"); //min index
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT(*obj1 == so);
    ret = mr1->getValue(&so, "Crater[i2]"); //max index
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT(*obj3 == so);
    ret = mr1->getValue(&so, "Crater[i3]"); //out of bounds +1
    CPPUNIT_ASSERT(0 != ret);
    ret = mr1->getValue(&so, "Crater[im1]"); //out of bounds -1
    CPPUNIT_ASSERT(0 != ret);
    ret = mr1->getValue(&so, "Crater[j0]"); //non existent index
    CPPUNIT_ASSERT(0 != ret);

    //testing getting a general Martian.
    //this part also includes the array bounds tests
    ret = mr1->getValue(&so, "Martian[i0]"); //min index
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT(*martian1 == so);
    ret = mr1->getValue(&so, "Martian[i2]"); //max index
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT(*martian3 == so);
    ret = mr1->getValue(&so, "Martian[i3]"); //out of bounds +1
    CPPUNIT_ASSERT(0 != ret);
    ret = mr1->getValue(&so, "Martian[im1]"); //out of bounds -1
    CPPUNIT_ASSERT(0 != ret);
    ret = mr1->getValue(&so, "Martian[j0]"); //non existent index
    CPPUNIT_ASSERT(0 != ret);

    //note for the testing:
    //the individual getters are tested in test-SpaceObject, so we're only testing the forwarding (not necessarily exhaustive) 
    
    Position pos0(1, 1);

    // Testing the individial elements on one example (indexes were )
    //testing the boulders elements
    ret = mr1->getValue(&pos, "Boulder[i0].Position"); 
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT(pos0 == pos);
    ret = mr1->getValue(&radius, "Boulder[i0].Radius"); 
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1, radius, 0.0001);
    ret = mr1->getValue(&x, "Boulder[i0].X"); 
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1, x, 0.0001);
    ret = mr1->getValue(&y, "Boulder[i0].Y"); 
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1, y, 0.0001);

    // Testing the individial elements on one example (indexes were )
    //testing the Craters elements
    ret = mr1->getValue(&pos, "Crater[i0].Position"); 
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT(pos0 == pos);
    ret = mr1->getValue(&radius, "Crater[i0].Radius"); 
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1, radius, 0.0001);
    ret = mr1->getValue(&x, "Crater[i0].X"); 
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1, x, 0.0001);
    ret = mr1->getValue(&y, "Crater[i0].Y"); 
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1, y, 0.0001);

    // Testing the individial elements on one example (indexes were )
    //testing the Martians elements
    ret = mr1->getValue(&pos, "Martian[i0].Position"); 
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT(pos0 == pos);
    ret = mr1->getValue(&radius, "Martian[i0].Radius"); 
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.5, radius, 0.0001);
    ret = mr1->getValue(&x, "Martian[i0].X"); 
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1, x, 0.0001);
    ret = mr1->getValue(&y, "Martian[i0].Y"); 
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1, y, 0.0001);
    ret = mr1->getValue(&heading, "Martian[i0].Heading"); 
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1, heading, 0.0001);
    ret = mr1->getValue(&speed, "Martian[i0].Speed"); 
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1, speed, 0.0001);
  }

void SpaceObjectRegisterTest::testSetValue() {
	int ret;
	double x=1, y=2, radius=3, heading=4, speed=5;
  Position pos_1_2(x, y);

    //testing indexes
    //this part also includes the array bounds tests
    ret = mr1->setValue(&y, DOUBLE, "Boulder[i0].Y"); //min index
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(2, mr1->Boulders[0].pos.getY(), 0.0001);
    ret = mr1->setValue(&y, DOUBLE, "Boulder[i2].Y"); //max index
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(2, mr1->Boulders[2].pos.getY(), 0.0001);
    ret = mr1->setValue(&y, DOUBLE, "Boulder[i3].Y"); //out of bounds +1
    CPPUNIT_ASSERT(0 != ret);
    ret = mr1->setValue(&y, DOUBLE, "Boulder[im1].Y"); //out of bounds -1
    CPPUNIT_ASSERT(0 != ret);
    ret = mr1->setValue(&y, DOUBLE, "Boulder[j0].Y"); //non existent index
    CPPUNIT_ASSERT(0 != ret);
    
    //note for the testing:
    //the individual getters are tested in test-SpaceObject, so we're only testing the forwarding (not necessarily exhaustive) 

    // Testing the individial elements on one example (indexes were )
    //testing the boulders elements
    ret = mr1->setValue(&pos_1_2, POSITION, "Boulder[i1].Position"); 
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT(pos_1_2 == mr1->Boulders[1].pos);
    ret = mr1->setValue(&radius, DOUBLE, "Boulder[i1].Radius"); 
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(3, mr1->Boulders[1].radius, 0.0001);
    ret = mr1->setValue(&x, DOUBLE,"Boulder[i1].X"); 
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1, mr1->Boulders[1].pos.getX(), 0.0001);
    ret = mr1->setValue(&y, DOUBLE,"Boulder[i1].Y"); 
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(2, mr1->Boulders[1].pos.getY(), 0.0001);

    //testing the Craters elements
    ret = mr1->setValue(&pos_1_2, POSITION, "Crater[i1].Position"); 
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT(pos_1_2 == mr1->Craters[1].pos);
    ret = mr1->setValue(&radius, DOUBLE, "Crater[i1].Radius"); 
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(3, mr1->Craters[1].radius, 0.0001);
    ret = mr1->setValue(&x, DOUBLE,"Crater[i1].X"); 
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1, mr1->Craters[1].pos.getX(), 0.0001);
    ret = mr1->setValue(&y, DOUBLE,"Crater[i1].Y"); 
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(2, mr1->Craters[1].pos.getY(), 0.0001);

    //testing the Martians elements
    ret = mr1->setValue(&pos_1_2, POSITION, "Martian[i1].Position"); 
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT(pos_1_2 == mr1->Martians[1].pos);
    ret = mr1->setValue(&radius, DOUBLE, "Martian[i1].Radius"); 
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(3, mr1->Martians[1].radius, 0.0001);
    ret = mr1->setValue(&x, DOUBLE,"Martian[i1].X"); 
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1, mr1->Martians[1].pos.getX(), 0.0001);
    ret = mr1->setValue(&y, DOUBLE,"Martian[i1].Y"); 
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(2, mr1->Martians[1].pos.getY(), 0.0001);
    ret = mr1->setValue(&heading, DOUBLE,"Martian[i1].Heading"); 
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(4, mr1->Martians[1].heading, 0.0001);
    ret = mr1->setValue(&speed, DOUBLE,"Martian[i1].Speed"); 
    CPPUNIT_ASSERT_EQUAL(0, ret);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(5, mr1->Martians[1].speed, 0.0001);
}
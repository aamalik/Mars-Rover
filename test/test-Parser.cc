#include <iostream>
#include <vector>

#include "test-Parser.h"
#include "Brain.hh"
#include "Parser.hh"
#include "InstructionIF.hh"
#include "ArgumentType.hh"


CPPUNIT_TEST_SUITE_REGISTRATION(ParserTest);

void ParserTest::setUp(){

}

void ParserTest::tearDown(){

}



void ParserTest::testParseFile(){

  vector<InstructionIF*> tmp;
  Brain * brainPtr;

  CPPUNIT_ASSERT(Parser::parseFile(&brainPtr,string(test1),0) == 0);
  
  delete brainPtr;
}

void ParserTest::testParseGetTypeImmediate() {
	ArgumentType t;

	CPPUNIT_ASSERT( !Parser::parseGetTypeImmediate(&t,"1") );
	CPPUNIT_ASSERT_EQUAL( INT, t );
	CPPUNIT_ASSERT( !Parser::parseGetTypeImmediate(&t,"1000") );
	CPPUNIT_ASSERT_EQUAL( INT, t );
	CPPUNIT_ASSERT( !Parser::parseGetTypeImmediate(&t,"-234567") );
	CPPUNIT_ASSERT_EQUAL( INT, t );

	CPPUNIT_ASSERT( !Parser::parseGetTypeImmediate(&t,"0.0001") );
	CPPUNIT_ASSERT_EQUAL( DOUBLE, t );
	CPPUNIT_ASSERT( !Parser::parseGetTypeImmediate(&t,"-1000.12345") );
	CPPUNIT_ASSERT_EQUAL( DOUBLE, t );
	CPPUNIT_ASSERT( !Parser::parseGetTypeImmediate(&t,"234567.891011") );
	CPPUNIT_ASSERT_EQUAL( DOUBLE, t );

	CPPUNIT_ASSERT( !Parser::parseGetTypeImmediate(&t,"*vara") );
	CPPUNIT_ASSERT_EQUAL( STRING, t );
	CPPUNIT_ASSERT( !Parser::parseGetTypeImmediate(&t,"*INTEGER") );
	CPPUNIT_ASSERT_EQUAL( STRING, t );
	CPPUNIT_ASSERT( !Parser::parseGetTypeImmediate(&t,"*aaabbb123") );
	CPPUNIT_ASSERT_EQUAL( STRING, t );


	CPPUNIT_ASSERT( Parser::parseGetTypeImmediate(&t,"*-0.0001") );
	CPPUNIT_ASSERT( Parser::parseGetTypeImmediate(&t,"#label") );
	CPPUNIT_ASSERT( Parser::parseGetTypeImmediate(&t,"withoutstar") );
	CPPUNIT_ASSERT( Parser::parseGetTypeImmediate(&t,"0.001a") );
	CPPUNIT_ASSERT( Parser::parseGetTypeImmediate(&t,"100x10") );
	CPPUNIT_ASSERT( Parser::parseGetTypeImmediate(&t,"0x10") );
	CPPUNIT_ASSERT( Parser::parseGetTypeImmediate(&t,"") );
}

void ParserTest::testParseImmediate() {

	int i;
	double d;
	string s;
	ArgumentType t;

	CPPUNIT_ASSERT( !Parser::parseGetTypeImmediate(&t,"1") );
	CPPUNIT_ASSERT_EQUAL( INT, t );
	CPPUNIT_ASSERT( !Parser::parseImmediate((void*)&i,"1"));
	CPPUNIT_ASSERT_EQUAL( 1, i );

	CPPUNIT_ASSERT( !Parser::parseGetTypeImmediate(&t,"1000") );
	CPPUNIT_ASSERT_EQUAL( INT, t );
	CPPUNIT_ASSERT( !Parser::parseImmediate((void*)&i,"1000"));
	CPPUNIT_ASSERT_EQUAL( 1000, i );

	CPPUNIT_ASSERT( !Parser::parseGetTypeImmediate(&t,"-234567") );
	CPPUNIT_ASSERT_EQUAL( INT, t );
	CPPUNIT_ASSERT( !Parser::parseImmediate((void*)&i,"-234567"));
	CPPUNIT_ASSERT_EQUAL( -234567, i );

	CPPUNIT_ASSERT( !Parser::parseGetTypeImmediate(&t,"0.0001") );
	CPPUNIT_ASSERT_EQUAL( DOUBLE, t );
	CPPUNIT_ASSERT( !Parser::parseImmediate((void*)&d,"0.0001"));
	CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.0001, d , DOUBLEPRECISION);

	CPPUNIT_ASSERT( !Parser::parseGetTypeImmediate(&t,"-1000.12345") );
	CPPUNIT_ASSERT_EQUAL( DOUBLE, t );
	CPPUNIT_ASSERT( !Parser::parseImmediate((void*)&d,"-1000.12345"));
	CPPUNIT_ASSERT_DOUBLES_EQUAL( -1000.12345, d , DOUBLEPRECISION);

	CPPUNIT_ASSERT( !Parser::parseGetTypeImmediate(&t,"234567.891011") );
	CPPUNIT_ASSERT_EQUAL( DOUBLE, t );
	CPPUNIT_ASSERT( !Parser::parseImmediate((void*)&d,"234567.891011"));
	CPPUNIT_ASSERT_DOUBLES_EQUAL( 234567.891011, d , DOUBLEPRECISION);

	CPPUNIT_ASSERT( !Parser::parseGetTypeImmediate(&t,"*vara") );
	CPPUNIT_ASSERT_EQUAL( STRING, t );
	CPPUNIT_ASSERT( !Parser::parseImmediate((void*)&s,"*vara"));
	CPPUNIT_ASSERT( s == "vara" );

	CPPUNIT_ASSERT( !Parser::parseGetTypeImmediate(&t,"*INTEGER") );
	CPPUNIT_ASSERT_EQUAL( STRING, t );
	CPPUNIT_ASSERT( !Parser::parseImmediate((void*)&s,"*INTEGER"));
	CPPUNIT_ASSERT( s == "INTEGER" );

	CPPUNIT_ASSERT( !Parser::parseGetTypeImmediate(&t,"*aaabbb123") );
	CPPUNIT_ASSERT_EQUAL( STRING, t );
	CPPUNIT_ASSERT( !Parser::parseImmediate((void*)&s,"*aaabbb123"));
	CPPUNIT_ASSERT( s == "aaabbb123" );

	CPPUNIT_ASSERT( Parser::parseImmediate((void*)&d,"*-0.0001") );
	CPPUNIT_ASSERT( Parser::parseImmediate((void*)&d,"#label") );
	CPPUNIT_ASSERT( Parser::parseImmediate((void*)&d,"withoutstar") );
	CPPUNIT_ASSERT( Parser::parseImmediate((void*)&d,"0.001a") );
	CPPUNIT_ASSERT( Parser::parseImmediate((void*)&d,"100x10") );
	CPPUNIT_ASSERT( Parser::parseImmediate((void*)&d,"0x10") );
	CPPUNIT_ASSERT( Parser::parseImmediate((void*)&d,"") );
}
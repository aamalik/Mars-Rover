#ifndef PARSER_TEST_H
#define PARSER_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include "Parser.hh"

class ParserTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(ParserTest);
  CPPUNIT_TEST(testParseFile);
  CPPUNIT_TEST(testParseGetTypeImmediate);
  CPPUNIT_TEST(testParseImmediate);
  CPPUNIT_TEST_SUITE_END();

#define test1 "extra/brainfiles/test1.asm"

 public:
  void setUp();
  void tearDown();
  void testParseFile();
  void testParseGetTypeImmediate();
  void testParseImmediate();
};

#endif

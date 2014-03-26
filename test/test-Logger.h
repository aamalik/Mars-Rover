#ifndef LOGGER_TEST_H
#define LOGGER_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include "Logger.hh"

#define BRAINFILE "extra/brainfiles/test1.asm"

class LoggerTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(LoggerTest);
  CPPUNIT_TEST(testSendMessageToBrain);
  CPPUNIT_TEST_SUITE_END();

 public:
  void setUp();
  void tearDown();
  void testSendMessageToBrain();

private:
	Logger *l;
};

#endif

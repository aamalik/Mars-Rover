#ifndef CONNECTION_TEST_H
#define CONNECTION_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include "Connection.hh"

#define BRAINFILE "extra/brainfiles/test1.asm"

class ConnectionTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(ConnectionTest);
  CPPUNIT_TEST(testAcceptConnection);
  CPPUNIT_TEST_SUITE_END();

 public:
  void setUp();
  void tearDown();
  void testAcceptConnection();

private:
  Connection *c1,*c2,*c3,*c4;
};

#endif

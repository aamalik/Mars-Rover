#ifndef SOCKET_TEST_H
#define SOCKET_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <iostream>
#include <Socket.hh>

using namespace std;

class SocketTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( SocketTest );
  CPPUNIT_TEST( testEnable );
  CPPUNIT_TEST( testReceive );
  CPPUNIT_TEST( testSendFunc );
  CPPUNIT_TEST_SUITE_END();

  Socket *s;

public:
  void setUp();
  void tearDown();
  void testEnable();
  void testReceive();
  void testSendFunc();
};

#endif  // SOCKET_TEST_H
/*
 * CounterTest.cpp
 *
 *  Created on: 2015/10/12
 *      Author: honor
 */




#include <cppunit/extensions/HelperMacros.h> // �i1�j
#include "Counter.h"

// �ȉ���CounterTest�N���X�̐錾-----
class CounterTest : public CPPUNIT_NS::TestFixture { // �i2�j
  CPPUNIT_TEST_SUITE( CounterTest ); // �i3�j
  CPPUNIT_TEST( test_init );         // �i4�j
  CPPUNIT_TEST( test_incr );         // �i4�j
  CPPUNIT_TEST( test_clear );        // �i4�j
  CPPUNIT_TEST_SUITE_END();          // �i5�j

protected:
  Counter* c_;

public:
  void setUp();      // �i6�j
  void tearDown();   // �i6�j

protected:
  void test_init();  // �i7�j
  void test_incr();  // �i7�j
  void test_clear(); // �i7�j
};

// �ȉ���CounterTest�N���X�̎���-----

CPPUNIT_TEST_SUITE_REGISTRATION( CounterTest ); // �i8�j

// �i6�j�e�e�X�g�E�P�[�X�̎��s���O�ɌĂ΂��
void CounterTest::setUp() {
  c_ = new Counter();
}

// �i6�j�e�e�X�g�E�P�[�X�̎��s����ɌĂ΂��
void CounterTest::tearDown() {
  delete c_;
}

// �i7�j����ȍ~�̓e�X�g�E�P�[�X�̎������e

void CounterTest::test_init() {
  CPPUNIT_ASSERT_EQUAL(0, c_->get()); // �i9�j
}

void CounterTest::test_incr() {
  for ( int i = 1; i < 10; ++i ) {
    c_->incr();
    CPPUNIT_ASSERT_EQUAL(i, c_->get()); // �i9�j
  }
}

void CounterTest::test_clear() {
  if ( c_->get() == 0 ) {
    c_->incr();
  }
  c_->clear();
  CPPUNIT_ASSERT_EQUAL(0, c_->get()); // �i9�j
}

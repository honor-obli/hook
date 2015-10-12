/*
 * CounterTest.cpp
 *
 *  Created on: 2015/10/12
 *      Author: honor
 */




#include <cppunit/extensions/HelperMacros.h> // （1）
#include "Counter.h"

// 以下はCounterTestクラスの宣言-----
class CounterTest : public CPPUNIT_NS::TestFixture { // （2）
  CPPUNIT_TEST_SUITE( CounterTest ); // （3）
  CPPUNIT_TEST( test_init );         // （4）
  CPPUNIT_TEST( test_incr );         // （4）
  CPPUNIT_TEST( test_clear );        // （4）
  CPPUNIT_TEST_SUITE_END();          // （5）

protected:
  Counter* c_;

public:
  void setUp();      // （6）
  void tearDown();   // （6）

protected:
  void test_init();  // （7）
  void test_incr();  // （7）
  void test_clear(); // （7）
};

// 以下はCounterTestクラスの実装-----

CPPUNIT_TEST_SUITE_REGISTRATION( CounterTest ); // （8）

// （6）各テスト・ケースの実行直前に呼ばれる
void CounterTest::setUp() {
  c_ = new Counter();
}

// （6）各テスト・ケースの実行直後に呼ばれる
void CounterTest::tearDown() {
  delete c_;
}

// （7）これ以降はテスト・ケースの実装内容

void CounterTest::test_init() {
  CPPUNIT_ASSERT_EQUAL(0, c_->get()); // （9）
}

void CounterTest::test_incr() {
  for ( int i = 1; i < 10; ++i ) {
    c_->incr();
    CPPUNIT_ASSERT_EQUAL(i, c_->get()); // （9）
  }
}

void CounterTest::test_clear() {
  if ( c_->get() == 0 ) {
    c_->incr();
  }
  c_->clear();
  CPPUNIT_ASSERT_EQUAL(0, c_->get()); // （9）
}

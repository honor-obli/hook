/*
 * func_test.cpp
 *
 *  Created on: 2015/10/12
 *      Author: honor
 */

#include <cppunit/extensions/HelperMacros.h>
#include "func.h"
#include "hook.h"

class func_test : public CPPUNIT_NS::TestFixture{

	CPPUNIT_TEST_SUITE(func_test);
	CPPUNIT_TEST(test_funcA);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp(){};
	void tearDown(){};

protected:
	void test_funcA();
};

CPPUNIT_TEST_SUITE_REGISTRATION( func_test );

void func_test::test_funcA(){
	CPPUNIT_ASSERT_EQUAL(3, funcA());
	UglyHotpatch((void*)&funcB, (void*)&stub_funcB);
	CPPUNIT_ASSERT_EQUAL(4, funcA());
	un_hook((void*)funcB);
	CPPUNIT_ASSERT_EQUAL(3, funcA());
}

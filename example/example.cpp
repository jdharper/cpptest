#include "cppTest.h"

// This function has a bug.  It is supposed to return
// the product of a and b but it actually returns the
// sum.

int product(int a, int b)
{
	return a + b;
}

DEF_GROUP(product);

DEF_TEST(product, Two_times_two)
{
	CHECK_EXPECT(product(2, 2), 4);
}

DEF_TEST(product, Two_times_three)
{
	CHECK_EXPECT(product(2, 3), 6);
}

int main()
{
	TestResult result;
	getTestRegistry()->run(result);
}
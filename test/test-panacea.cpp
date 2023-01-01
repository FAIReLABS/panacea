#define BOOST_TEST_MODULE Helpers

#include "panacea.hpp"

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(PanaceaSuite)

BOOST_AUTO_TEST_CASE(StringTrim)
{
	/* space delimited */
	std::string str1(" string ");
	std::string str2("string");
	str1 = trim_str(str1);
	BOOST_CHECK_EQUAL(str1, str2);

	/* tabe delimited */
	str1 = "	string	";
	str1 = trim_str(str1);
	BOOST_CHECK_EQUAL(str1, str2);
}

BOOST_AUTO_TEST_CASE(DetectOperator)
{
	std::string str("numeric   : 42");
	std::string op = detect_assign_operator(str);
	BOOST_CHECK_EQUAL(op, ":");

	str = "numeric   : 42 um";
	op = detect_assign_operator(str);
	BOOST_CHECK_EQUAL(op, ":");

	str = "foo = 42 / bar = -41 / baz = 40";
	op = detect_assign_operator(str);
	BOOST_CHECK_EQUAL(op, "=");

	str = "foo = 42  bar = -41  baz = 40";
	op = detect_assign_operator(str);
	BOOST_CHECK_EQUAL(op, "=");

	str = "foo = 42 : bar = -41 : baz = 40";
	op = detect_assign_operator(str);
	BOOST_CHECK_EQUAL(op, "=");

	str = "compounded numeric   : x=-12761 um / y=-13469 um / z=3709 um";
	op = detect_assign_operator(str);
	BOOST_CHECK_EQUAL(op, "=");

	str = "compounded numeric   : x=-12761 um / y=-13469 um / z=3709 um / compounded numeric   : x=-12761 um / y=-13469 um / z=3709 um";
	op = detect_assign_operator(str);
	BOOST_CHECK_EQUAL(op, "=");

	str = "double compounded numeric   : compounded numeric   : x=-12761 um / y=-13469 um / z=3709 um";
	op = detect_assign_operator(str);
	BOOST_CHECK_EQUAL(op, "=");

	str = "Lorem Ipsum (numeric : 42) Lorem Ipsum";
	op = detect_assign_operator(str);
	BOOST_CHECK_EQUAL(op, ":");

	str = "Lorem Ipsum (numeric) : 42";
	op = detect_assign_operator(str);
	BOOST_CHECK_EQUAL(op, ":");

	str = "Lorem Ipsum (numeric) : 42 /";
	op = detect_assign_operator(str);
	BOOST_CHECK_EQUAL(op, ":");
	
	str = "Lorem Ipsum (numeric) : 42 )";
	op = detect_assign_operator(str);
	BOOST_CHECK_EQUAL(op, ":");
}

BOOST_AUTO_TEST_SUITE_END()
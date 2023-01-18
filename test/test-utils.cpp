#include <boost/test/unit_test.hpp>
#include "panacea.hpp"

BOOST_AUTO_TEST_SUITE(UtilsSuite)

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

BOOST_AUTO_TEST_SUITE_END()
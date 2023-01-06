#include "panacea.hpp"

/* determine the assignement operators for unambigous case of numerical assignement */
std::string detect_assign_operator(std::string st)
{
	// holds regex results
	std::smatch assign_match;

	// unambigous case of numerical assignement
	std::regex assign_regex("(([:=]+?)\\s*)(?=([-+]?[0-9]*\\.[0-9]+|[-+]?[0-9]+))");

	// std::string weak_search;
	std::string out;

	// search
	while (regex_search(st, assign_match, assign_regex))
	{
		// return
		out = assign_match[2];
		// return suffix until no more text
		st = assign_match.suffix();
	}

	// std::cout << "Assignement operator: " << out << '\n';

	return out;

}

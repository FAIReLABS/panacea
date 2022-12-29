#include "panacea.hpp"

std::vector<std::string> detect_numeric_vars(std::string st, std::regex regex)
{
	// holds regex results
	std::smatch hits;
	std::vector<std::string> search_out;

	while (regex_search(st, hits, regex))
	{
		print_regex(hits);
	
		// return suffix until no more text
		st = hits.suffix();
	}

	return search_out;
}

#include "panacea.hpp"

/* Trim the white spaces from both ends of results */
std::string trim_str(std::string x)
{
	std::regex white_reg("^[ |\\t|\\n|\\r|\\v|\\f]*|[ |\\t|\\n|\\r|\\v|\\f]*$");
	x = std::regex_replace(x, white_reg, "");
	return x;
}

void print_regex(std::smatch hits, bool verbose)
{
	
	if (verbose) 
	{
		// before regex match
		std::cout << "Prefix: " << hits.prefix() << '\n';
	
		// subgroups
		for (size_t i = 0; i < hits.size(); ++i)
			std::cout << i << ": " << std::quoted(hits[i].str()) << '\n';

		// behind regex match
		std::cout << "Suffix: " <<  hits.suffix() << '\n';

	} else {
		// print triplets 
		std::cout << "Variable: " << std::quoted(trim_str(hits[3])) << '\n';
		std::cout << "Value: " << trim_str(hits[5]) << '\n';
		std::cout << "Unit: " << trim_str(hits[6]) << '\n';

	}
}


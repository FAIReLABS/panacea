#include "panacea.hpp"

/* Trim the white spaces from both ends of results */
std::string trim_str(std::string x)
{
	std::regex white_reg("^[ |\\t|\\n|\\r|\\v|\\f]*|[ |\\t|\\n|\\r|\\v|\\f]*$");
	x = std::regex_replace(x, white_reg, "");
	return x;
}

void print_regex(std::smatch hits, bool verbose, int charn)
{
	
	if (verbose) 
	{
		// before regex match
		std::cout << "Prefix: " << std::quoted(hits.prefix().str()) << '\n';
	
		// subgroups
		for (size_t i = 0; i < hits.size(); ++i)
			std::cout << i << ": " << std::quoted(hits[i].str()) << '\n';

		// behind regex match
		std::cout << "Suffix: " <<  std::quoted(hits.suffix().str()) << '\n';

	} else {
		// print triplets 
		/* std::cout << "Field: " << "" << '\n'; */
		
		std::cout << "Char: " << charn << '\n';
		std::cout << "Variable: " << trim_str(hits[2]) << '\n';
		std::cout << "Value: " << trim_str(hits[3]) << '\n';
		std::cout << "Unit: " << trim_str(hits[4]) << '\n';
		std::cout << '\n';

	}
}


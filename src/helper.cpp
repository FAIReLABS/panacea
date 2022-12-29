#include "panacea.hpp"

void print_regex(std::smatch hits)
{
/* 	// before regex match
	std::cout << "Prefix: " << hits.prefix() << '\n';
	
	// subgroups
	for (size_t i = 0; i < hits.size(); ++i) 
		std::cout << i << ": " << std::quoted(hits[i].str()) << '\n'; 

	// behind regex match	
	std::cout << "Suffix: " <<  hits.suffix() << '\n';
	 */

	std::cout << "Variable: " << hits[3] << '\n';
	std::cout << "Value: " << hits[5] << '\n'; 
	std::cout << "Unit: " << hits[6] << '\n'; 

}


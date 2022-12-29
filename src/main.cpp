#include "panacea.hpp"

int main(int argc, char **argv)
{
	std::cout << argv[1] << std::endl;
	// ifstream is used for reading files
	std::ifstream inf{ argv[1] };

	// If we couldn't open the output file stream for reading
	if (!inf) 
	{
		// Print an error and exit
		std::cerr << "Could not be opened for reading!\n";
		return 1;
	}
	
	// let user assign variable name
	std::string user_input{"."};
	std::cout << "Enter variable:\n";
	std::cin >> user_input;

	while (inf) 
	{
		
		// read stuff from the file into a string and print it
		std::string file_input;
		std::getline(inf, file_input);

		// print regex matches
		std::vector<std::string> pr;

		// phase 1 - detect assignment operator
		std::string assign_operator = detect_assign_operator(file_input);

		// phase 2 - if phase 1 true then extract assignement of numeric variables
		if (!assign_operator.empty()) 
		{
			std::regex rg = regex_numeric_vars(assign_operator, user_input);
			pr = detect_numeric_vars(file_input, rg);
		}
		
	}

	return 0;

	// When inf goes out of scope, the ifstream
	// destructor will close the file
}
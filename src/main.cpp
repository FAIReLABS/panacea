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

	/* store line output as chunks*/
	std::vector<std::string> chunk; 

	while (inf) 
	{
		// read from the file into a string and print it
		std::string line_input;
		std::getline(inf, line_input);

		// phase 1 - detect assignment operator
		std::string assign_operator = detect_assign_operator(line_input);

		// phase 2 - if phase 1 true then extract assignement of numeric variables
		if (!assign_operator.empty()) 
		{
			detect_numeric_vars(line_input, assign_operator, user_input);
		}

		// phase 3 - otherwise check wether text might include tables
		if (assign_operator.empty())
		{
			detect_tables(line_input, chunk); 
		}
	}

	// phase 4 - use results of phase 2 as gold labels to detect nominal variable value pairs

	return 0;

	// When inf goes out of scope, the ifstream
	// destructor will close the file
}
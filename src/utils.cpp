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

// parse results column wise (works if inner vectors are of same size)
std::vector<std::vector<std::string>> transpose_table(std::vector<std::vector<std::string>> table)
{

	// store
	std::vector<std::vector<std::string>> out(table[0].size(), std::vector<std::string>(table.size()));

	for (std::vector<std::string>::size_type i = 0; i < table[0].size(); i++)
	{ 
		for (std::vector<std::string>::size_type j = 0; j < table.size(); j++) 
		{
			out[i][j] = table[j][i];
		}
	}

	return out;
}

std::vector<std::vector<int>> transpose_table(std::vector<std::vector<int>> table)
{

	// store
	std::vector<std::vector<int>> out(table[0].size(), std::vector<int>(table.size()));

	for (std::vector<int>::size_type i = 0; i < table[0].size(); i++)
	{ 
		for (std::vector<int>::size_type j = 0; j < table.size(); j++) 
		{
			out[i][j] = table[j][i];
		}
	}

	return out;
}

// Function for counting spaces
int cnt_chars(std::string st)
{
	// input sentence
	char *buf = new char[st.length() + 1];
	strcpy(buf, st.c_str());
	char ch = buf[0];
	int i{0};
	int count{0};

	// counting spaces
	while (ch != '\0') {
		ch = buf[i];
		if (!isspace(ch))
			count++;
		i++;
	}

	// returning number of spaces
	return (count);
}
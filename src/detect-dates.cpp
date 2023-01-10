#include "panacea.hpp"

bool detect_dates(std::string st, int &field_num, int &line_num)
{
	// create regex
	std::regex rg("^(.*)" + std::string(dat) + "(\\t|\\n|\\r|\\v|\\f|\\s*$)");

	// holds regex results
	std::smatch hits;

	// position of first character
	int charn{1};
	bool is_date;

	is_date = regex_search(st, hits, rg);
	
	// for lines field numbers are not the same as line numbers as fields only record hits
	if (is_date)
	{
		field_num++;
		charn +=  hits[1].length(); // get start of triplet

		// print the date
		std::cout << "Field: " << field_num << '\n';
		std::cout << "Line: " << line_num << '\n';
		std::cout << "Char: " << charn << '\n';
		std::cout << "Date: " << hits[2] << '\n';
		std::cout << '\n';
	}

	return is_date;
}
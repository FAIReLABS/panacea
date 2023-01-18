#include "config.hpp" // autoconf
#include "panacea.hpp"

bool detect_dates(std::string line_input, int &field_num, int &line_num, 
	panacea &out)
{
	// create regex
	std::regex rg("^(.*)" + std::string(date_rg) + "(\\t|\\n|\\r|\\v|\\f|\\s*$)");

	// holds regex results
	std::smatch hits;

	// position of first character
	int charn{1};
	bool is_date;

	is_date = regex_search(line_input, hits, rg);
	
	// for lines field numbers are not the same as line numbers as fields only record hits
	if (is_date)
	{
		field_num++;
		charn +=  hits[1].length(); // get start of triplet

		// print the date
		out.update(hits[2].str(), "date");
	}

	return is_date;
}
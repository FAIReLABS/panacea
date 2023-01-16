#include "panacea.hpp"

std::string paste_punct_values(std::string x,  std::string collapse)
{

	std::set<std::string> punct = {",", ":", "=", "/"};
	punct.erase(x);
	
	// for initial value no OR
	std::string out = *punct.begin(); 
	// collapse map based on ordered vector of values
	for (auto i = ++punct.begin(); i != punct.end(); ++i) {
		// for the remainder seperatre with OR
		out += collapse + *i;
	}

	return out;

}

std::regex regex_numeric_vars(std::string assign_operator, std::string user)
{

	std::string punct = paste_punct_values(assign_operator, "");

	// negate assign operator
	std::string not_assign_operator = "[^" + assign_operator + "]";
	
	// variable
	std::string var; 
	// possible user input
	if (user != ".") 
	{
		not_assign_operator += "*?"; // for partial matches
		var = not_assign_operator + user + not_assign_operator;
	} 
	else 
	{
		var = not_assign_operator + "+?"; // requires at least on hit for char that is not a seperator
	}
	var = "(" + var + ")";

	std::string punct_begin = "\\((?=[^" + assign_operator + "\\)]+" + assign_operator + not_assign_operator + "+\\))|[" + punct + "]"; 
	std::string punct_end = "[" + punct + "\\)]";

	// assignement operator
	assign_operator = "(?:" + assign_operator + ")\\s*?"; 

	// boundaries
	std::string begin = "(" + not_assign_operator + "+(?:" + punct_begin + ")+)?"; // begin of triplet
	std::string end = "(?:\\s*" + punct_end + "|\\s{2,}|\\t|\\n|\\r|\\v|\\f|\\s*$)"; // end of triplet

	/* std::cout <<  begin + var + assign_operator + num + unit + end << '\n'; */

	// cast to regex type and return
	std::string st =  begin + var + assign_operator + num + unit + end ;
	return std::regex(st.c_str());

}

void detect_numeric_vars(std::string line_input, std::string assign_operator, int &field_num, int &line_num, panacea &out)
{
	// create regex
	std::regex rg = regex_numeric_vars(assign_operator, ".");

	// holds regex results
	std::smatch hits;

	// position of first character
	int charn{1};

	while (regex_search(line_input, hits, rg))
	{

		// for lines field numbers are not the same as line numbers as fields only record hits
		field_num++;

		// get start of triplet
		charn +=  hits[1].length();

		// detect units
		std::string var;
		const std::string &val = hits[3].str();
		std::string unit;
		detect_units(hits, var, unit);

		// print the triplet
		/* print_regex(var, val, unit, field_num, line_num, charn); */
		out.combine(panacea{ var, unit, val, field_num, line_num, charn });

		// get end of triplet
		charn += hits[0].length();
	
		// return suffix until no more text
		line_input = hits.suffix();
	}

}
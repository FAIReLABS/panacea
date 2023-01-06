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
	assign_operator = "(" + assign_operator + ")\\s*?"; 

	// boundaries
	std::string begin = "(" + not_assign_operator + "+(" + punct_begin + ")+)?"; // begin of triplet
	std::string end = "(\\s*?" + punct_end + "|\\s*?$|\\s{2}?)"; // end of triplet

	/* std::cout <<  begin + var + assign_operator + num + unit + end << '\n'; */

	// cast to regex type and return
	std::string st =  begin + var + assign_operator + std::string(num_lz) + std::string(unit_lz) + end ;
	return std::regex(st.c_str());

}

void detect_numeric_vars(std::string st, std::string assign_operator, std::string user_input)
{
	// create regex
	std::regex rg = regex_numeric_vars(assign_operator, user_input);

	// holds regex results
	std::smatch hits;
	std::vector<std::string> search_out;

	while (regex_search(st, hits, rg))
	{

		print_regex(hits, false);
	
		// return suffix until no more text
		st = hits.suffix();
	}

	/* return search_out; */
}

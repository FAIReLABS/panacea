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

/* determine the assignement operators for unambigous case of numerical assignement */
std::string detect_assign_operator(std::string st)
{
	// holds regex results
	std::smatch assign_match;

	// unambigous case of numerical assignement
	std::regex assign_regex("(([:=]+?)\\s*)(?=([-+]?[0-9]*\\.[0-9]+|[-+]?[0-9]+))");

	// std::string weak_search;
	std::string out;

	// search
	while (regex_search(st, assign_match, assign_regex))
	{
		// return
		out = assign_match[2];
		// return suffix until no more text
		st = assign_match.suffix();
	}

	// std::cout << "Assignement operator: " << out << '\n';

	return out;

}

std::regex regex_numeric_vars(std::string assign_operator, std::string user)
{

	std::string punct = paste_punct_values(assign_operator, "");
	std::string punct_begin = "[" + punct + "\\(]";
	std::string punct_end = "[" + punct + "\\)]";

	// negate assign operator
	std::string not_assign_operator = "[^" + assign_operator + "]";
	
	// variable
	std::string var; 
	// possible user input
	if (user != ".") 
	{
		not_assign_operator += "*?"; // for partial matches
		var = not_assign_operator + user + not_assign_operator;
	} else {
		var = not_assign_operator + "+?"; // requires at least on hit for char that is not a seperator
	}
	var = "(" + var + ")";

	// assignement operator
	assign_operator = "(" + assign_operator + ")\\s*?"; 

	std::string num = "([-+]??[0-9]*?\\.[0-9]+?|[-+]??[0-9]+?)"; // numeric 
	std::string unit = "\\s*?\\(??([a-zA-Z%]+)??\\)??\\s??"; // unit

	// boundaries
	std::string begin = "(^" + not_assign_operator + "+(" + punct_begin + ")+)?"; // begin of triplet
	std::string end = "(" + punct_end + "|$|\\s{2}?)"; // end of triplet

	// std::cout <<  begin + var + assign_operator + num + unit + end << '\n';

	// cast to regex type and return
	std::string st =  begin + var + assign_operator + num + unit + end ;
	return std::regex(st.c_str());

}


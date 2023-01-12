#include "panacea.hpp"

/* Trim the white spaces from both ends of results */
std::string trim_str(std::string x)
{
	std::regex white_reg("^[ |\\t|\\n|\\r|\\v|\\f]*|[ |\\t|\\n|\\r|\\v|\\f]*$");
	x = std::regex_replace(x, white_reg, "");
	return x;
}

// filter units within variable names
void detect_units(std::match_results<std::string::const_iterator> st, std::string &var, std::string &unit)
{
	// trim whitespace
	var = trim_str(st[2].str());
	unit = trim_str(st[4].str());
		
	std::smatch hits_unit;
	std::regex rg_unit("(?:.*)(\\s*\\(\\s*([a-zA-Z%\\.]+[-]?[0-9]?)\\s*\\))");
	
	bool grep_unit = regex_search(var, hits_unit, rg_unit);
	if (grep_unit)
	{
		unit = hits_unit[2].str();
		var.erase(var.find(hits_unit[1].str()), hits_unit[1].str().size());
	} 
}

void detect_units(std::string st, std::string &var, std::string &unit)
{
	// trim whitespace
	var = trim_str(st);
		
	std::smatch hits_unit;
	std::regex rg_unit("(?:.*)(\\s*\\(\\s*([a-zA-Z%\\.]+[-]?[0-9]?)\\s*\\))");
	
	bool grep_unit = regex_search(var, hits_unit, rg_unit);
	if (grep_unit)
	{
		unit = hits_unit[2].str();
		var.erase(var.find(hits_unit[1].str()), hits_unit[1].str().size());
	} 
}


void print_regex(std::smatch hits, const int &charn, const int &field_num, const int &line_num)
{
	
	// detect units
	std::string var;
	std::string unit;
	detect_units(hits, var, unit);
	
	std::cout << "Field: " << field_num << '\n';
	std::cout << "Line: " << line_num << '\n';
	std::cout << "Char: " << charn << '\n';
	std::cout << "Variable: " << var << '\n';
	std::cout << "Value: " << hits[3] << '\n';
	std::cout << "Unit: " << unit << '\n';
	std::cout << '\n';

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

// Calculate median of vector container.
double median(std::vector<int> x)
{
	// if length one then shortcut
	if (x.size() == 1)
		return static_cast<double>(x[0]);

	// sort vector
	std::sort(x.begin(), x.end());

	// calculate median
	double median = (x[x.size() / 2] + x[(x.size() / 2) - 1]) / 2;
	return median;
}
double median(std::vector<double> x)
{
	// if length one then shortcut
	if (x.size() == 1)
		return x[0];

	// sort vector
	std::sort(x.begin(), x.end());

	// calculate median
	double median = (x[x.size() / 2] + x[(x.size() / 2) - 1]) / 2;
	return median;
}
 
// Calculate the median deviation.
double mad(std::vector<int> x)
{

	// if length one then shortcut
	if (x.size() == 1)
		return static_cast<double>(x[0]);

	std::vector<double> mad;
	double med = median(x);
	for (const auto &i: x)
	{
		mad.push_back(abs(i - med));
	}
	return median(mad);
}
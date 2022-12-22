#include <iostream>
#include <fstream> // file reading
#include <string> //
#include <regex>
#include <vector>
#include <iterator>
#include <numeric>

std::regex create_regex(std::string sep) 
{
	std::string st;
	// let user assign variable name
	std::cout << "Enter variable:\n";
	std::cin >> st;

	// combine to form regex
	if (st != ".") {

		st += "(.*?)(";
	// include punctuation
		st += sep + "+?)";

	} else {

		st = "([a-zA-Z\\s\\.\\(\\)]+?)\\s*(:+?)\\s*[-+]?([0-9]*\\.[0-9]+|[0-9]+)(\\s)";
	}

	// cast to regex type and return
	return std::regex(st.c_str());
}

void print_regex(std::smatch hits)
{
/* 	// before regex match
	std::cout << "Prefix: " << hits.prefix() << '\n';
	
	// subgroups
	for (size_t i = 0; i < hits.size(); ++i) 
		std::cout << i << ": " << hits[i] << '\n'; 

	// behind regex match	
	std::cout << "Suffix: " << hits.suffix() << '\n'; */

	std::cout << "Variable: " << hits[1] << '\n';
	std::cout << "Value: " << hits[3] << '\n';


}

std::vector<std::string> decompose_text(std::string st, std::regex rg)
{
	// holds regex results
	std::smatch sm;

	std::vector<std::string> out;

	while(regex_search(st, sm, rg)) {
		
		// print
		print_regex(sm);

		// vector holds result
		out.push_back(static_cast<std::string>(sm[0]));
		out.push_back(static_cast<std::string>(sm.suffix()));

		// return suffix until no more text
		st = sm.suffix();
	}

	return out;
}

std::multimap<int, std::string> char_frq(std::string fil, std::vector<std::string> rg)
{

	// save hits
	std::multimap<int, std::string> sum;

	for (const auto &i: rg) {
	
		// get regex and add spaces 
		std::string add_space;
		add_space = ("\\s*" + i) + "\\s*";
		std::regex reg(add_space.c_str());

		// open file
		std::ifstream inf(fil.c_str());
	
		// intermediate save
		int sub{0};

		while (inf) {

			// read stuff from the file into a string and print it
			std::string strInput;
			std::getline(inf, strInput);

			// iterators for begin and end
			auto hits = std::sregex_iterator(strInput.begin(), strInput.end(), reg);  
			auto end = std::sregex_iterator();
			
			// extract the hit number
			if (std::distance(hits, end)) 
				sub += std::distance(hits, end);

		};
		
		// add element iteratively (most efficient)
		// sum.push_back(sub);
		sum.insert(std::make_pair(sub, i));
		
		// inf.close();

	};

	return sum;	

}

int main()
{
	// ifstream is used for reading files
	std::ifstream inf{ "extdata/2018-01-19-GLENDON/2018-01-19-GLENDON_1_1.chk_is" };

	// If we couldn't open the output file stream for reading
	if (!inf) {
		// Print an error and exit
		std::cerr << "Could not be opened for reading!\n";
		return 1;
	}

	// count punctuation
	std::vector<std::string> reg{":", "=", "\\/", "\\(.*\\)"}; //
	std::multimap<int, std::string>  table;
	table = char_frq("extdata/2018-01-19-GLENDON/2018-01-19-GLENDON_1_1.chk_is", reg);

	// frequencies punctuation
	for (const auto &i : table) {
		std::cout << "Character '"  << i.second << "' has been found: " << i.first << " times\n";
	}

	// most abundant punctuation (I need to use mapping here)
	
	auto pr = std::max_element(table.begin(), table.end(), [](const auto &x, const auto &y) { return x.second > y.second; });
	std::string sep_one{pr->second};
	// std::cout << pr->second << std::endl; 

	// Define a regex pattern
	std::regex var = create_regex(sep_one);

	while (inf) {
		
		// read stuff from the file into a string and print it
		std::string strInput;
		std::getline(inf, strInput);

		// print regex matches
		std::vector<std::string> pr;
		pr = decompose_text(strInput, var);
		
	}

	return 0;

	// When inf goes out of scope, the ifstream
	// destructor will close the file
}
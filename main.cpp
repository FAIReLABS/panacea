#include <iostream>
#include <fstream> // file reading
#include <string> //
#include <regex>
#include <vector>
#include <iterator>
#include <numeric>

std::regex create_regex(std::string sep) 
{
	// let user assign variable name
	std::cout << "Enter variable:\n";
	std::string st;
	std::cin >> st;

	// combine to form regex
	st += "(.*?)(";
	// include punctuation
	st += sep + "+?)";  
	
	// cast to regex type and return
	return std::regex(st.c_str());
}

void print_regex(std::string st, std::regex rg)
{
	// holds regex results
	std::smatch sm;

	while(regex_search(st, sm, rg)){
		
		// before regex match
		std::cout << "Prefix: " << sm.prefix() << '\n';
		
		// subgroups
		for (size_t i = 0; i < sm.size(); ++i) 
			std::cout << i << ": " << sm[i] << '\n'; 

		// behind regex match	
		std::cout << "Suffix: " << sm.suffix() << '\n';
		st = sm.suffix();
	}
}

std::vector<int> char_frq(std::string fil, std::vector<std::string> rg)
{

	// save hits
	std::vector<int> sum;

	for (const auto &i: rg) {
	
		// get regex
		std::regex reg(i.c_str());

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
		sum.push_back(sub);

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
	std::vector<std::string> reg{"\\s*:\\s*", "\\s*\\=\\s*", "\\s*\\/\\s*"}; //
	std::vector<int> table(0);
	table = char_frq("extdata/2018-01-19-GLENDON/2018-01-19-GLENDON_1_1.chk_is", reg);

	// total counts punctuation
	double tot{0};
	for (const auto &i : table) {
		tot += i;
	}

	// frequencies punctuation
	for (auto &i : table) {
		double freq{0};
		freq = i / tot;
		std::cout << "Frequency: " << freq << '\n';
	}

	// most abundant punctuation (I need to use mapping here)
	std::string sep_one{":"};

	// Define a regex pattern
	std::regex var = create_regex(sep_one);

	while (inf) {
		
		// read stuff from the file into a string and print it
		std::string strInput;
		std::getline(inf, strInput);

		// print regex matches
		print_regex(strInput, var);
		
	}

	return 0;

	// When inf goes out of scope, the ifstream
	// destructor will close the file
}
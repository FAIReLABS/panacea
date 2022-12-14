#include <iostream>
#include <fstream> // file reading
#include <string> //
#include <regex>

std::regex create_regex() 
{
	// let user assign variable name
	std::cout << "Enter variable:\n";
	std::string st;
	std::cin >> st;

	// combine to form regex
	st += "(.*?)(:+?)";  
	
	// cast to regex type and return
	return static_cast<std::regex>(st);
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

int main()
{
	// ifstream is used for reading files
	std::ifstream inf{ "extdata/2018-01-19-GLENDON/2018-01-19-GLENDON_1_1.chk_is" };

	// Define a regex pattern
	std::regex reg = create_regex();

	// If we couldn't open the output file stream for reading
	if (!inf){
		// Print an error and exit
		std::cerr << "Could not be opened for reading!\n";
		return 1;
	}

	while (inf) {
		
		// read stuff from the file into a string and print it
		std::string strInput;
		std::getline(inf, strInput);

		// print regex matches
		print_regex(strInput, reg);
		
		// auto st = regex_search(strInput, sm, reg);
		// how man times can it be found in th line
		// auto hits = std::sregex_iterator(strInput.begin(), strInput.end(), reg);  
		// auto end = std::sregex_iterator();
		// extract the hit number
		// std::cout << "Found " << std::distance(hits, end) << " hits\n";
		// replace parts of the text
		// std::string new_s = std::regex_replace(strInput, reg, "[$&]");        
		// std::cout << new_s << '\n';
		// print all
		//std::cout << strInput << '\n'; 
	}

	return 0;

	// When inf goes out of scope, the ifstream
	// destructor will close the file
}
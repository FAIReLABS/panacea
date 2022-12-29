#include "panacea.hpp"

std::multimap<int, std::string, std::greater<int>> char_frq(std::string fil, std::vector<std::string> rg)
{

	// save hits (custom ordering based on int with comperator = third argument)
	std::multimap<int, std::string, std::greater<int>> sum;

	for (const auto &i: rg) {
	
		// get regex and add spaces (need to use c strings for this .c_str())
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
		sum.insert(std::make_pair(sub, i));
		

	};

	// frequencies punctuation
	for (const auto &i: sum) {
		std::cout << "Character '" << i.second << "' has been found " << i.first << "times \n";
	}

	return sum;

}

// most abundant punctuation (I need to use mapping here)
	// auto pr = std::max_element(table.begin(), table.end(), [](const auto &x, const auto &y) { return x.second > y.second; });
	
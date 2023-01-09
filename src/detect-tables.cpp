#include "panacea.hpp"

// row storage of  potential columns
std::vector<int> parse_line(std::string line, std::vector<std::string> &row, 	std::vector<int> &pos)
{

	// storage containers
	std::smatch hits; // matches
	std::vector<int> out; // integers for determening whether this could be a table
	
	// position of char
	int charn{1};
	int rem{0};

	// make regex (include spaces before and behind to enable character position counts)
	std::string rgnum = "(\\s+|^)" + std::string(num) + "(\\s+|$)";
	std::regex rg(rgnum.c_str());

	// decompose potential tables
	while (regex_search(line, hits, rg))
	{

		// when not all space then this must be nominal
		std::string pre = hits.prefix();
		if (!std::all_of(pre.begin(), pre.end(), isspace))
		{
			out.push_back(0);
			row.push_back(pre);
			pos.push_back(charn);
		}

		// this must be numeric
		if (hits[2] != "")
		{
			out.push_back(1);
			row.push_back(hits[2]);
			charn += hits[1].length() + (pre.length() - rem);
			pos.push_back(charn);
		}

		// when the original regex_search is false for the postfix then this remainder of the string must be nominal
		line = hits[3].str() + hits.suffix().str();
		std::smatch inner;
		// return character position to start of loop with space character position after hit
		charn += hits[2].length() + hits[3].length();
		// remainder of suffix length when removing spaces in front
		rem = hits[3].length();

		if (!(line == "" || regex_search(line, inner, rg)))
		{
			out.push_back(0);
			row.push_back(line);
			pos.push_back(charn);
		}



		/* helper */
		// print_regex(hits, true);

	}

	return out;
}

// detecting tables
bool is_table(std::vector<std::string> &chunk, std::vector<std::vector<std::string>> &table, std::vector<std::vector<int>> &origin) 
{
	// store relative counts characters
	double rel_cnt;
	// store table values
	int j{0};
	// count many times there appear to be columns
	int k{0};
	// store previous vector of ints
	std::vector<int> int_add;	

	/* turn chunk lines into integer vectors with 1 represting numerics and
	0 representing nominals */
	for (auto i: chunk) 
	{
		// store values of row
		std::vector<std::string> row;
		// store positions of values
		std::vector<int> pos;
		// store integer representation
		std::vector<int> int_line = parse_line(i, row, pos);

		// add rows to table
		if (!row.empty())
			table.push_back(row);
		
		// add rows to table
		if (!pos.empty())
			origin.push_back(pos);

		// bump number to count number of lines containing possible columns
		if (!int_line.empty())
			++k;

		// initial resizes fills with 0, also in reversed order
		if (int_line.size() < int_add.size())
			int_line.resize(int_add.size());
		else
			int_add.resize(int_line.size());

		// add integer representations of text lines together
		for (size_t j = 0; j < int_line.size(); ++j) 
		{
			// if size equal then add values
			int_add[j] += int_line[j];
		}

		// print helper
		/* for (const auto &i: int_add) 
		{
			std::cout << i;
		}
		std::cout << '\n'; */

		/* count characters per line */
		int cnt = cnt_chars(i);
		rel_cnt += (cnt / 100.0);
	}

	// this is the first table check if all numeric columns align then the matrix should reduce to 0
	if (k > 0) // if at least 1 line of potential table
	{	 
		for (const auto &i: int_add) 
		{
			j += i % k;
			/* std::cout << (i) << '\n'; */
		}
		/* std::cout << j << '\n'; */
	}
	else
	{
		j = 1; 
	}
	
	// this is the second table check if this is a table this number should be low (range: 0-1)
	if (chunk.size() > 0) // if at least chunk size 1 line
		rel_cnt = rel_cnt / chunk.size();
	
/* 	std::cout << "Amount of characters relative to white space: " << std::fixed << rel_cnt << '\n'; */

	bool out = (j == 0 && rel_cnt < 0.6) ? true : false;

	/* std::cout << "Is this a table: " << out << '\n'; */
	
	return out;
}

/* extract chunks of text that might be tables */
void detect_tables(std::string line_input, std::vector<std::string> &chunk) 
{

	/* accumulate untile empty line then flush */
	if (!line_input.empty())
	{
		chunk.push_back(line_input);
	} 
	
	if (line_input.empty() || std::all_of(line_input.begin(), line_input.end(),isspace))
	{
		// store potential table values
		std::vector<std::vector<std::string>> table;
		// store position of values
		std::vector<std::vector<int>> origin;

		// check whether it is a table
		if (is_table(chunk, table, origin))
		{

			// transpose tables
			std::vector<std::vector<std::string>> colwise_table = transpose_table(table); 
			std::vector<std::vector<int>> colwise_origin = transpose_table(origin); 
			
			// check
			/* std::cout << "original: " << table.size() << '\n';
			std::cout << "new: " << colwise.size() << '\n'; */
			for (size_t i = 0; i < colwise_table.size(); i++)
			{
				std::cout << "Char: ";
				for (size_t j = 0; j < colwise_origin[i].size(); j++)
					std::cout << " " << colwise_origin[i][j] << " ";
				std::cout << '\n';
				std::cout << "Variable: \n";
				std::cout << "Value: ";
				for (size_t j = 0; j < colwise_table[i].size(); j++)
					std::cout << " " << trim_str(colwise_table[i][j]) << " ";
				std::cout << '\n';
			}

			std::cout << '\n';
		}

		/* std::cout << "<Empty line>\n"; */

		// finally finish with a clean up
		chunk.clear();
	}

}

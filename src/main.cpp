/*
 * This file is part of panacea.
 *
 * Developed for FAIReLABS: Integrated lab solutions for an open science lab.
 * 
 * This product includes software developed by FAIReLABS
 * (https://fairelabs.github.io/webpage/).
 * 
 * See the COPYRIGHT file at the top-level directory of this distribution
 * for details of code ownership.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "panacea.hpp"

// flags to main
void main_args(int argc, char **argv, std::string &data, std::string &output, 
	double &white, int verbose){
	
	int i = 0;
	
	for (i = 1; i < argc; i++)
	{
		// uneven are flags
		if (i % 2 == 0) 
			continue;

		if (strcmp(argv[i], "--data") == 0)
		{
			data = argv[i + 1]; // input file
		}
		else if (strcmp(argv[i], "--output") == 0)
		{
			output = argv[i + 1]; // output file
		}
		else if (strcmp(argv[i], "--white") == 0)
		{
			std::string str(argv[i + 1]); // whitespace sensitivity
			white = std::stod(str);
		}
		else if (strcmp(argv[i], "--verbose") == 0)
		{
			std::string str(argv[i + 1]); // verbosity
			white = std::stoi(str);
		}
		else
		{
			std::cerr << "Unkown flag!\n";
		}
	}
}	

int main(int argc, char **argv)
{

	// input/output
	std::string data, output;
	// white space sensitivity
	double white{ 0.7 };
	// white space sensitivity
	int verbose{ 0 };
	// evaluate input
	main_args(argc, argv, data, output, white, verbose);

	if (verbose)
		std::cout << "Input file: " << data << '\n';

	// ifstream is used for reading files
	std::ifstream inf{ data.c_str() };

	// If we couldn't open the output file stream for reading
	if (!inf) 
	{
		// Print an error and exit
		std::cerr << "Could not be opened for reading!\n";
		return 1;
	}

	// positions
	int line_num{ 0 }; // count line numbers 
	int field_num{ 0 }; // count chunk numbers
	int white_lines{ 0 }; // count white lines

	// store line output as chunks
	std::vector<std::string> chunk; 
	// intermediate storage of lines for chunks
	std::vector<int> chunk_lines; 
	// results
	panacea results;

	while (inf) 
	{
		// read from the file into a string and print it
		std::string line_input;
		std::getline(inf, line_input);

		// count lines
		line_num++; 

		// phase 0 - detect dates
		bool grep_date = detect_dates(line_input, field_num, line_num, results);

		// phase 1 - detect assignment operator
		std::string assign_operator = detect_assign_operator(line_input);

		// phase 2 - if phase 1 true then extract assignement of numeric variables
		if (!grep_date && !assign_operator.empty()) 
		{
			detect_numeric_vars(line_input, assign_operator, field_num, line_num, results);
		}

		// phase 3 - otherwise check wether text might include tables
		if (!grep_date && assign_operator.empty())
		{
			detect_tables(line_input, chunk, field_num, line_num, chunk_lines, white, white_lines, results); 
		}

	}

	// print
	if (verbose)
		print(std::cout, results);

	// write prettified JSON to another file
	nlohmann::ordered_json j = parse(results);
	std::ofstream ouf { output.c_str() };
	ouf << std::setw(4) << j << std::endl;

	// phase 4 - use results of phase 2 as gold labels to detect nominal variable value pairs

	return 0;

	// When inf goes out of scope, the ifstream
	// destructor will close the file
}
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

/** @file panacea.hpp
 * @brief Global variables and functions of panacea. 
 * 
 */

#ifndef PANACEA_HPP
#define PANACEA_HPP

#include <iostream>
#include <fstream> // file reading
#include <string> // strings
#include <regex> // regular expressions
#include <vector> // vectors
#include <iterator>
#include <numeric>
#include <iomanip> // quote strings
#include <set> // variable list
#include <algorithm> // for eg min element  
#include <list>


/**
 * @brief Aggregate class for variable, value, unit triplets
 * 
 */
struct triplet
{
	// triplets
	std::string var; 
	std::string unit;
	std::vector<std::string> val; // can be multiple
};

/**
 * @brief Aggregate class for location of triplets
 * 
 */
struct locator
{
	// location
	int field;
	std::vector<int> line; // can be multiple
	std::vector<int> charn; // can be multiple
};

/**
 * @brief Implementation of panacea data integration
 *
 * Integration is controlled on a per triplet basis; variable, value, and unit. 
 * Triplets are accompanied by a set of locator coordinates which allow 
 * reconstructing relative positions of the triplets within the original file.
 */
class panacea
{
	// typedefs
	typedef std::string cell; /**< a single entity of the triplet. */ 
	typedef std::vector<std::string> column; /**< a series of entities of a triplet. */ 
	typedef std::vector<std::vector<std::string>> table; /**< a matrix of entities of a set of triplets. */
	typedef std::vector<int> range; /**< a range of coordinates of a triplet */
	typedef std::vector<std::vector<int>> ident; /**< a matrix of coordinates referring to a table */

	// friend functions
	friend std::ostream &print(std::ostream &os, const panacea &dat);

public:

	//--------------------------------------------------------------------------
	// constructors
	//--------------------------------------------------------------------------
	/**
	 * @brief Construct a new panacea object
	 * 
	 * Panacea objects can be constructed from individual entities (variable,
	 * unit, value) and their coordinates (field number, line number and 
	 * position of first character). Alternatively, columns or whole tables can 
	 * be supplied.
	 */
	panacea() = default;
	// table wise initialize
	panacea(column var, column unit, table val, int field, range line, ident charn)
	{
		for (size_t i = 0; i < val.size(); i++)
			trip.push_back(triplet{var[i], unit[i], val[i]});
		
		for (size_t i = 0; i < charn.size(); i++)
			loc.push_back(locator{field, line, charn[i]});

	};
	// column wise initialize
	panacea(cell var, cell unit, column val, int field, range line, range charn) :
			trip(1, triplet{ var, unit, val  }), 
			loc(1, locator{ field, line, charn  })
	{};
	// cell wise initialize
	panacea(cell var, cell unit, cell val, int field, int line, int charn) :
			trip(1, triplet{ var, unit, column{ val } }), 
			loc(1, locator{ field, range{ line }, range{ charn }})
	{};
	// date wise initialize
	panacea(cell datum) : date(datum) {};

	//--------------------------------------------------------------------------
	// member operations
	//--------------------------------------------------------------------------
	/**
	 * @brief Combine to panacea objects
	 * 
	 * @return panacea& 
	 */
	panacea &combine(const panacea&);
	/**
	 * @brief Update a data member
	 * 
	 * @param x The content of an entity to be replaced.
	 * @param mem The data member on which to perform the operation.
	 * @return panacea& 
	 */
	panacea &update(cell x, std::string mem);

private:

	//--------------------------------------------------------------------------
	// data members
	//--------------------------------------------------------------------------

	cell date;
	std::vector<triplet> trip;
	std::vector<locator> loc;

};

/**
 * @brief Print panacea objects.
 * 
 * @param os Ostream object reference.
 * @param dat Reference to panacea object to be printed.
 * @return std::ostream& 
 */
std::ostream &print(std::ostream &os, const panacea &dat);

/**
 * @brief Detecting dates in a text file.
 *
 * This detects dates in several coventional formats as listed below.
 *
 * @param line_input std::string container with the original text from 
 * 	the document.
 * @param field_num reference to integer value of the text field that yielded 
 * 	the result (accumulative count in the respective document).
 * @param line_num reference to integer value of the line number that yielded 
 * 	the result (accumulative count in the respective document).
 * 
 * @htmlinclude
 * @return boolean true if date detected, otherwise returns false.
 */
bool detect_dates(std::string line_input, int &field_num, int &line_num, 
	panacea &out);

/**
 * @brief Detecting assignement operators in a text file.
 *
 * This detects asssignement operators such as often used to connect 
 * variable--value pairs.
 * 
 * @param line_input std::string container with the original text from 
 * 	the document.
 * 
 * @return std::string container returning the assignement operator of 
 * 	the respective text line.
 */
std::string detect_assign_operator(std::string line_input);

/**
 * @brief Detecting numeric value--variable pairs in a text file.
 *
 * This detects variable--value pairs consisting of numeric values with 
 * the following types:
 * 	- integers (e.g. -42)
 * 	- floating point (e.g. -42.42)
 * 	- scientific (e.g. -42.42e-42)
 * Optionally, the unit of the numeric value is returned.
 *  
 * @param line_input std::string container with the original text from 
 * 	the document.
 * @param assign_operator std::string container returning the assignement operator of 
 * 	the respective text line.
 * @param field_num reference to integer value of the text field that yielded 
 * 	the result (accumulative count in the respective document).
 * @param line_num reference to integer value of the line number that yielded 
 * 	the result (accumulative count in the respective document).
 */
void detect_numeric_vars(std::string line_input, std::string assign_operator, 
	int &field_num, int &line_num, panacea &out);

/**
 * @brief Detecting tables in the file.
 * 
 * Detects tables in files based on four prerequisites:
 * 	1. repeating patterns exist
 * 	2. if the text field spans more than lines
 * 	3. the relative abundance of white space (can be modified)
 * 	4. if the lines follow each in consecutive order with interuptions not larger than 1 white line
 *
 * @param line_input std::string container with the original text from 
 * 	the document.
 * @param chunk reference to a std::vector of std::strings container that 
 * 	store consecutive lines of text.
 * @param field_num reference to integer value of the text field that yielded 
 * 	the result (accumulative count in the respective document).
 * @param line_num reference to integer value of the line number that yielded 
 * 	the result (accumulative count in the respective document).
 * @param chunk_lines reference to a vector of type int storing the line number 
 * 	that yielded the result of the chunk (accumulative count in the respective chunk).
 * @param white relative abundance of white space (defaults to double of 0.7).
 */
void detect_tables(std::string line_input, std::vector<std::string> &chunk, 
	int &field_num, int &line_num, std::vector<int> &chunk_lines, 
	const double &white, int &white_lines, panacea &out);

/**
 * @brief Detecting units
 * 
 * Detecting units in string based on common patterns. This
 * function seperates variables from units, thereby returning both
 * as a result.
 *
 * @param hits smatch type of regex for variable-value pairs.
 * @param var string reference to store the variable string.
 * @param unit string reference to store the unit string.
 */
void detect_units(std::match_results<std::string::const_iterator> hits, std::string &var, std::string &unit);

/**
 * @brief Detecting units
 * 
 * Detecting units in string based on common patterns. This
 * function seperates variables from units, thereby returning both
 * as a result.
 *
 * @overload
 * 
 * @param hits string container with variable-value pairs.
 * @param var string reference to store the variable string.
 * @param unit string reference to store the unit string.
 */
void detect_units(std::string hits, std::string &var, std::string &unit);

/**
 * @brief Trim whitespace at beginning and end of string
 * 
 * @param x string container
 * @return string container exclusive trailing and preceding white spaces.
 */
inline std::string trim_str(std::string x)
{
	std::regex white_reg("^[ |\\t|\\n|\\r|\\v|\\f]*|[ |\\t|\\n|\\r|\\v|\\f]*$");
	x = std::regex_replace(x, white_reg, "");
	return x;
}

/**
 * @brief Calculate median of vector container.
 * 
 *
 * @param x a vector container of type double. 
 * @return a double precision value.
 */
double median(std::vector<int> x);

/**
 * @brief Calculate median of vector container.
 * 
 * @overload
 * @param x a vector container of type double. 
 * @return a double precision value.
 */
double median(std::vector<double> x);
 
/**
 * @brief Calculate the median deviation.
 * 
 *
 * @param x a vector container of type double.
 * @return  a double precision value.
 */
double mad(std::vector<int> x);

/**
 * @brief transpose a table of strings.
 * 
 * Tranposing a table (effectively a matrix).
 *
 * @param table a vector container with vector containers of type string. 
 * @return a vector container with vector containers of type string.
 */
std::vector<std::vector<std::string>> transpose_table(std::vector<std::vector<std::string>> table);

/**
 * @brief transpose a table of integers.
 * 
 * @overload
 *
 * @param table a vector container with vector containers of type integer. 
 * @return a vector container with vector containers of type integer.
 */
std::vector<std::vector<int>> transpose_table(std::vector<std::vector<int>> table);


/**
 * @brief Count characters.
 * 
 *
 * @param st string container. 
 * @return number of characters counted.
 */
int cnt_chars(std::string st);

/**
 * @brief Regex dates.
 * 
 */
constexpr char dat[] =  "((0[1-9]|[12][0-9]|3[01])[- \\/\\.](0[1-9]|1[012])[- \\/\\.](19|20)?\\d\\d(\\s+(0[1-9]|1[0-9]|2[0-4]):[0-5][0-9])?)";

/**	
 * @brief Regex numeric values.
 * 
 * integers (e.g. -42) = [-+]?[0-9]+
 * float (e.g. -42.42) = [-+]?[0-9]+\\.[0-9]+
 * scientific (e.g. -42.42e-42) = [-+]?[0-9]+(?:\\.[0-9]+)?[eE][-+]?[0-9]+
 */ 
constexpr char num[] = "([-+]?[0-9]+|[-+]?[0-9]+\\.[0-9]+|[-+]?[0-9]+(?:\\.[0-9]+)?[eE][-+]?[0-9]+)";

/**
 * @brief Regex units.
 * 
 */
constexpr char unit[] = "(?:\\s*\\(?\\s*([a-zA-Z%]+[-]?[0-9]?)\\s*\\)?)?"; ;

#endif
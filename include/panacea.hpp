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
bool detect_dates(std::string line_input, int &field_num, int &line_num);

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
void detect_numeric_vars(std::string line_input, std::string assign_operator, int &field_num, int &line_num);

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
void detect_tables(std::string line_input, std::vector<std::string> &chunk, int &field_num, int &line_num, std::vector<int> &chunk_lines, const double &white, int &white_lines);

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
std::string trim_str(std::string x);

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
 * @brief print the results of a regex match.
 * 
 *
 * @param hits smatch type result of regex search. 
 * @param charn reference to character number counting from the beginning of the line.
 * @param field_num reference to integer value of the text field that yielded 
 * 	the result (accumulative count in the respective document).
 * @param line_num reference to integer value of the line number that yielded 
 * 	the result (accumulative count in the respective document).
 */
void print_regex(std::smatch hits, const int &charn, const int &field_num, const int &line_num);

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
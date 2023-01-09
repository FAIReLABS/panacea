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
#include <algorithm> // for eg max  

//------------------------------
// Function forward declarations
//------------------------------

// phase 1 - detecting assignement operator
std::string detect_assign_operator(std::string st);

// phase 2 - detecting numeric vars
void detect_numeric_vars(std::string st, std::string assign_operator, std::string user_input);

// phase 3 - detecting tables
void detect_tables(std::string line_input, std::vector<std::string> &chunk);

// helper functions
std::string trim_str(std::string x);
void print_regex(std::smatch hits, bool verbose, int charn);
std::vector<std::vector<std::string>> transpose_table(std::vector<std::vector<std::string>> table);
std::vector<std::vector<int>> transpose_table(std::vector<std::vector<int>> table);
int cnt_chars(std::string st);

// regex for detecting values
constexpr char num[] = "([-+]?[0-9]+\\.[0-9]+|[-+]?[0-9]+)"; // detect numeric values
constexpr char unit[] = "(?:\\s*\\(?\\s*([a-zA-Z%]+[-]?[0-9]?)\\s*\\)?)?"; // detect units;

#endif
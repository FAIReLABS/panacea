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

//------------------------------
// Function forward declarations
//------------------------------

// phase 0 - detecting dates
bool detect_dates(std::string st, int &field_num, int &line_num);

// phase 1 - detecting assignement operator
std::string detect_assign_operator(std::string st);

// phase 2 - detecting numeric vars
void detect_numeric_vars(std::string st, std::string assign_operator, std::string user_input,int &field_num, int &line_num);

// phase 3 - detecting tables
void detect_tables(std::string line_input, std::vector<std::string> &chunk, int &field_num, int &line_num, std::vector<int> &chunk_lines);

// helper functions
std::string trim_str(std::string x);
void print_regex(std::smatch hits, bool verbose, const int &charn, const int &field_num, const int &line_num);
std::vector<std::vector<std::string>> transpose_table(std::vector<std::vector<std::string>> table);
std::vector<std::vector<int>> transpose_table(std::vector<std::vector<int>> table);
int cnt_chars(std::string st);
void detect_units(std::match_results<std::string::const_iterator> hits, std::string &var, std::string &unit);
void detect_units(std::string hits, std::string &var, std::string &unit);

// regex for detecting values
constexpr char dat[] =  "((0[1-9]|[12][0-9]|3[01])[- \\/\\.](0[1-9]|1[012])[- \\/\\.](19|20)?\\d\\d(\\s+(0[1-9]|1[0-9]|2[0-4]):[0-5][0-9])?)";
constexpr char num[] = "([-+]?[0-9]+\\.[0-9]+|[-+]?[0-9]+)"; // detect numeric values
constexpr char unit[] = "(?:\\s*\\(?\\s*([a-zA-Z%]+[-]?[0-9]?)\\s*\\)?)?"; // detect units;

#endif

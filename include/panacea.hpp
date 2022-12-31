#ifndef PANACEA_HPP
#define PANACEA_HPP

#include <iostream>
#include <fstream> // file reading
#include <string> //
#include <regex>
#include <vector>
#include <iterator>
#include <numeric>
#include <iomanip>
#include <set>

// Function forward declarations
// std::regex create_regex(std::string sep);
std::string detect_assign_operator(std::string st);
std::vector<std::string>  detect_numeric_vars(std::string st, std::regex regex);
void print_regex(std::smatch hits, bool verbose);
std::multimap<int, std::string, std::greater<int>> char_frq(std::string fil, std::vector<std::string> rg);
std::regex regex_numeric_vars(std::string assign_operator, std::string user);


#endif
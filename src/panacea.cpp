#include "panacea.hpp"

// member functions
panacea &panacea::update(cell x, std::string mem)
{
	// combine triplets
	if (mem == "date") 
		date = x;
	return *this;
}

panacea &panacea::combine(const panacea &rhs)
{
	// combine triplets
	trip.insert(trip.end(), rhs.trip.begin(), rhs.trip.end());
	return *this;
}

// friend functions
std::ostream &print(std::ostream& os, const panacea &dat)
{
	
	os << dat.date << '\n';
	os << '\n';

	for (const auto &i: dat.trip)
	{ 
		os << "Variable: " << i.var << '\n'; 
		os << "Value: ";
		for (const auto j: i.val)
			os << trim_str(j) << " ";
		os << '\n';
		os << "Unit: " << i.unit << '\n';
		os << '\n';
	}
	
	return os;
}
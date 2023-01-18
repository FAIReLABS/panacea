#include "config.hpp" // autoconf
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
	// combine locator
	loc.insert(loc.end(), rhs.loc.begin(), rhs.loc.end());
	return *this;
}

// friend functions
std::ostream &print(std::ostream& os, const panacea &dat)
{
	
	// os << dat.date << '\n';
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

#if HAVE_NLOHMANN_JSON_HPP
nlohmann::ordered_json parse(const panacea &dat)
{
	nlohmann::ordered_json k;
	for(size_t i = 0; i < dat.loc.size(); ++i)
	{ 
		// intialize storage vector
		nlohmann::ordered_json j;

		j["Variable"] = dat.trip[i].var;

		// can be multiple
		nlohmann::json l_vec = dat.trip[i].val;
		j["Value"] = l_vec;

		j["Unit"] = dat.trip[i].unit;

		j["Text field"] = dat.loc[i].field;

		// can be multiple
		nlohmann::json m_vec = dat.loc[i].line;
		j["Line number"] = m_vec;

		// can be multiple
		nlohmann::json j_vec = dat.loc[i].charn;
		j["Character number"] = j_vec;

		// store rowwise json
		k.push_back(j);
	}

	return k;
}
#endif
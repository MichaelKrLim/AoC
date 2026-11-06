#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>
#include <vector>

int	main()
{
	struct Range { unsigned	long long lower{0},	upper{0}; };
	std::ifstream input{"5_2.in"};
	std::vector<Range> ranges{};
	for(std::string	line{""}; std::getline(input,line) && !line.empty();)
	{
		Range current_range;
		char ignore;
		std::istringstream iss{line};
		iss>>current_range.lower>>ignore>>current_range.upper;

		auto lower_range_it{std::ranges::find_if(ranges,[&](const Range& range){ return	current_range.lower>=range.lower &&	current_range.lower<=range.upper; })};
		auto upper_range_it{std::ranges::find_if(ranges,[&](const Range& range){ return	current_range.upper>=range.lower &&	current_range.upper<=range.upper; })};
		if(lower_range_it==ranges.end()	&& upper_range_it==ranges.end()) //	already	non-overlapping	range
		{
			std::erase_if(ranges,[&](const Range& range){ return range.lower>=current_range.lower && range.upper<=current_range.upper; });
			ranges.insert(std::ranges::lower_bound(ranges,current_range.upper,{},[](const Range& range){ return	range.lower; }),current_range);
		}
		else if(lower_range_it==upper_range_it)	// fully contained in range
			continue;
		else if(lower_range_it!=ranges.end() &&	upper_range_it!=ranges.end())
		{
			lower_range_it->upper=upper_range_it->upper;
			ranges.erase(lower_range_it+1,upper_range_it+1);
		}
		else if(lower_range_it!=ranges.end()) // in	lower range, extend	up
			lower_range_it->upper=current_range.upper;
		else if(upper_range_it!=ranges.end()) // in	upper range, extend	down
			upper_range_it->lower=current_range.lower;
	}
	std::cout<<std::accumulate(ranges.begin(),ranges.end(),0ull,[](auto	acc, const Range& range)
	{
		return acc+range.upper-range.lower+1;
	})<<"\n";
}

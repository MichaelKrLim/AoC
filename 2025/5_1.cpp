#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

int main()
{
	struct Range
	{
		unsigned long long lower{0},upper{0};
	};
	std::ifstream input{"5_1.in"};
	std::vector<Range> ranges;
	long result;
	for(std::string line{""}; std::getline(input,line) && !line.empty();)
	{
		unsigned long long lower,upper;
		char ignore;
		std::istringstream iss{line};
		iss>>lower>>ignore>>upper;
		ranges.push_back(Range{lower,upper});
	}
	for(unsigned long long id; input>>id;)
	{
		for(int i{0}; i<ranges.size(); ++i)
		{
			if(ranges[i].lower<=id && ranges[i].upper>=id)
			{
				++result;
				break;
			}
		}
	}
	std::cout<<result<<"\n";
}

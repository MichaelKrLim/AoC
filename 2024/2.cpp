#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <fstream>
#include <iterator>
#include <sstream>
#include <vector>

std::vector<int> sub_vector(std::vector<int> levels, int i)
{
	std::vector<int> subv;
	subv.reserve(levels.size()-1);
	subv.insert(subv.begin(), levels.begin(), levels.begin()+i);
	subv.insert(subv.end(), levels.begin()+i+1, levels.end());
	return subv;
}

bool is_safe(std::vector<int> levels)
{
	std::vector<int> differences{};
	differences.reserve(levels.size()-1);
	for(int i{}; i<levels.size()-1; ++i)
	{
		differences.push_back(levels[i+1] - levels[i]);
	}
	return std::all_of(differences.begin(), differences.end(), [](const int& x){ return x >= 1 && x <= 3; }) || 
	std::all_of(differences.begin(), differences.end(), [](const int& x){ return x <= -1 && x >= -3; });
}

int main()
{
	std::ifstream in("2.in");
	std::string line;
	long long result{0};
	while(getline(in, line))
	{
		std::istringstream iss(line);
		std::vector<int> levels(std::istream_iterator<int>{iss},{});
		for(std::size_t i{0}; i<levels.size(); ++i)
		{
			if(is_safe(sub_vector(levels, i)))
			{
				++result;
				break;
			}
		}
	}
	std::cout << result << "\n";
}
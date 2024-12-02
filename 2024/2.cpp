#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>

std::vector<int> sub_vector(std::vector<int> levels, int i)
{
	std::vector<int> subv;
	subv.reserve(levels.size()-1);
	subv.insert(subv.begin(), levels.begin(), levels.begin()+i);
	subv.insert(subv.end(), levels.begin()+i+1, levels.end());
	return subv;
}

int main()
{
	long long result{0};
	std::ifstream in("2.in");
	std::string line;
	while(getline(in, line))
	{
		std::istringstream iss(line);
		std::vector<int> levels(std::istream_iterator<int>{iss}, {});
		bool has_failed{false};
		if(!std::ranges::is_sorted(levels))
		{
			for(std::size_t i{0}; i<levels.size(); ++i)
			{
				const auto subv = sub_vector(levels, i);
				if(std::ranges::is_sorted(subv))
				{
					has_failed = true;
					levels = std::move(subv);
					break;
				}
			}
			if(!has_failed)
				continue;
		}

		struct Data
		{
			std::size_t index;
			bool has_failed;
			std::vector<int> levels;
			bool succeeded;
		};
		std::stack<Data> st{};
		st.push({0, has_failed, levels, true});
		while(!st.empty())
		{
			auto [index, current_has_failed, current_levels, current_succeeded] = st.top();
			st.pop();
			for(std::size_t i{index}; i<current_levels.size()-1; ++i)
			{
				const auto difference = std::abs(current_levels[i]-current_levels[i+1]);
				if(difference > 3 || difference == 0)
				{
					if(!has_failed)
					{
						st.push({index-1, true, sub_vector(current_levels, i), true});
						st.push({index, true, sub_vector(current_levels, i+1), true});
					}
					current_succeeded = false;
					break;
				}
			}
			if(current_succeeded)
			{
				++result;
				break;
			}
		}
	}
	std::cout << result << "\n";
}

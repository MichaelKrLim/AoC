#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <string>
#include <ranges>

bool breaks_ordering_rules(const int lhs, const std::vector<int>& lower_priorities)
{
	if(std::ranges::find(lower_priorities, lhs) != lower_priorities.end())
		return true;
	return false;
}

[[nodiscard]] std::vector<int> get_update(const std::string& line)
{
	std::vector<int> update;
	std::istringstream iss(line);
	std::string	digit;
	while(getline(iss, digit, ','))
		update.push_back(std::stoi(digit));
	return update;
}

int	main()
{
	struct Priority
	{
		int	page, priority{0};
		Priority(int page) : page(page)	{};
	};
	unsigned long long result{0};
	std::ifstream in("5.in");
	std::string	line{};
	std::vector<std::vector<int>> priorities(100);
	while(getline(in, line))
	{
		if(line	== "")
			break;
		std::istringstream iss(line);
		int	higher, lower;
		char c;
		iss	>> higher >> c >> lower;
		priorities[higher].push_back(lower);
	}

	std::vector<int> update;
	for(std::size_t i{0}; getline(in, line); ++i)
	{
		update = get_update(line);
		bool rearranged{false};
		for(std::size_t j{1}; j<update.size(); ++j)
		{
			for(std::size_t g{j}; breaks_ordering_rules(update[g-1], priorities[update[g]]); --g)
			{
				rearranged = true;
				std::swap(update[g], update[g-1]);
			}
		}
		if(rearranged)
			result += update[update.size()/2];
	}
	std::cout << result;
}

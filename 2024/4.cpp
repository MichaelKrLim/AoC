#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <unordered_map>
#include <vector>

unsigned long long explore_diagonals(const std::vector<std::string>& input, int x, int y)
{
	const bool valid_right_diagonal = (input[y+1][x+1] == 'M' && input[y-1][x-1] == 'S') ||
									  (input[y+1][x+1] == 'S' && input[y-1][x-1] == 'M'),
	valid_left_diagonal 			= (input[y+1][x-1] == 'M' && input[y-1][x+1] == 'S') ||
									  (input[y+1][x-1] == 'S' && input[y-1][x+1] == 'M');
	if(valid_right_diagonal && valid_left_diagonal)
		return 1;	
	return 0;
}

int main()
{
	std::ifstream in("4.in");
	std::vector<std::string> input(std::istream_iterator<std::string>{in}, {});
	unsigned long long result{0};
	for(int y{1}; y<input.size()-1; ++y)
	{
		for(int x{1}; x<input[0].size()-1; ++x)
		{
			if(input[y][x] == 'A')
				result += explore_diagonals(input, x, y);
		}
	}
	std::cout << result << "\n";
}

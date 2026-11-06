#include <bits/stdc++.h>

struct Config
{
	std::vector<int> required_values;
};

struct Button
{
	std::vector<int> affected_indices;
};

struct Machine
{
	Config config;
	std::vector<Button> buttons;
};

std::istream& operator>>(std::istream& is, Config& config)
{
	config.required_values.clear();
	char ignore;
	for(int value{0}; is>>ignore && ignore!='}';)
	{
		is>>value;
		config.required_values.push_back(value);
	}
	return is;
}

std::istream& operator>>(std::istream& is, Button& button)
{
	button.affected_indices.clear();
	char ignore;
	for(int value{0}; is>>ignore && ignore != ')';)
	{
		is>>value;
		button.affected_indices.push_back(value);
	}
	return is;
}

std::istream& operator>>(std::istream& is, Machine& machine)
{
	machine.buttons.clear();
	std::string line;
	std::getline(is,line);
	std::istringstream iss{line};
	for(std::string block{""}; iss>>block;)
	{
		std::istringstream values{block};
		switch (block.front())
		{
			case '[':
				break;
			case '{':
				values>>machine.config;
				break;
			case '(':
			{
				Button new_button;
				values>>new_button;
				machine.buttons.push_back(new_button);
				break;
			}
		}
	}
	return is;
}

int main()
{
	std::vector<Machine> lines{std::istream_iterator<Machine>{std::cin},{}};
	for(const Machine& machine : lines)
	{
		std::vector<std::valarray<int>> matrix(machine.buttons.size(),std::valarray(0,machine.config.required_values.size()+1));
		for(int i{0}; i<machine.buttons.size(); ++i)
		{
			for(const int affected_index : machine.buttons[i].affected_indices)
				matrix[i][affected_index]=1;
			matrix[i][machine.config.required_values.size()]=machine.config.required_values[i];
		}
		int used_rows{0};
		std::vector<int> free_indices;
		for(int x{0}; x<machine.config.required_values.size(); ++x)
		{
			auto unused_row_it{std::find_if(matrix.begin()+used_rows,matrix.end(),[&](const auto& row)
			{
				return row[x]!=0;
			})};
			if(unused_row_it==matrix.end())
			{
				free_indices.emplace_back(x);
				continue;
			}
			else
				std::swap(*unused_row_it,matrix[used_rows]);
			for(int y{0}; y<machine.buttons.size(); ++y)
			{
				if(matrix[y][x]==0 || std::distance(matrix.begin(),unused_row_it)==y)
					continue;

				const std::valarray<int> scaled{matrix[used_rows]*matrix[y][0]};
				matrix[y]*=matrix[used_rows][x];
				matrix[y]-=scaled;
			}
			++used_rows;
		}
		for(const auto& row : matrix)
		{
			for(const auto& val : row)
			{
				std::cout<<val<<' ';
			} std::cout<<"\n";
		}
	}
}

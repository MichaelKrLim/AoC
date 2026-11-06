#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>

enum class Direction
{
	north, east, south, west
};

int to_offset(const Direction& direction)
{
	switch(direction)
	{
		case Direction::north:
			return -1;
		case Direction::east:
			return 1;
		case Direction::south:
			return 1;
		case Direction::west:
			return -1;
	}
}

struct Position
{
	int	x, y;
	Direction direction	= Direction::north;

	bool operator==(const Position&	rhs) const = default;
	bool operator!=(const Position&) const = default;
};

namespace std 
{
	template <>
	struct hash<Position> 
	{
		size_t operator()(const	Position& key) const 
		{
			size_t h1 =	std::hash<int>{}(key.x);
			size_t h2 =	std::hash<int>{}(key.y);
			return h1 ^	(h2	<< 1);
		}
	};
}

Position move(Position guard_position)
{
	if(guard_position.direction	== Direction::north	|| guard_position.direction	== Direction::south)
		guard_position.y +=	to_offset(guard_position.direction);
	else
		guard_position.x +=	to_offset(guard_position.direction);
	return guard_position;
}

Position turn(Position position)
{
	if(position.direction == Direction::north)
		position.direction = Direction::east;
	else if(position.direction == Direction::east)
		position.direction = Direction::south;
	else if	(position.direction	== Direction::south)
		position.direction = Direction::west;
	else if	(position.direction	== Direction::west)
		position.direction = Direction::north;
	return position;
}

bool valid_position(const Position&	position, const	auto& board)
{
	return position.x >	-1 && position.x < board[0].size() && position.y > -1 && position.y	< board.size();
}

int	main()
{
	Position guard_position(0, 0, Direction::north), starting_position;
	std::vector<std::vector<bool>> visited{};
	long long result{0};
	std::vector<std::vector<bool>> board{};
	std::ifstream in("6.in");
	std::string	line;
	for(std::size_t	y{0}; getline(in, line); ++y)
	{
		std::vector<bool> row{};
		for(std::size_t	x{0}; x	< line.size(); ++x)
		{
			if(line[x] == '^')
			{
				guard_position.x = x;
				guard_position.y = y;
				row.push_back(false);
			}
			else if(line[x] == '.')
				row.push_back(false);
			else
				row.push_back(true);
		}
		board.push_back(row);
	}
	visited.resize(board.size(), std::vector<bool>(board[0].size(), false));
	starting_position =	guard_position;
	do
	{
		std::cout << guard_position.x << ' ' << guard_position.y << ' ' << static_cast<int>(guard_position.direction) << "\n";
		if(!visited[guard_position.y][guard_position.x])
		{
			++result;
			visited[guard_position.y][guard_position.x] = true;
		}

		Position next_position = move(guard_position);
		if(!valid_position(next_position, board))
		{
			std::cout << result	<< "\n";
			return 0;
		}
		for(int	i{0}; i<4; ++i)
		{
			if(board[next_position.y][next_position.x] == true)
			{
				next_position =	turn(guard_position);
				next_position =	move(next_position);
				if(!valid_position(next_position, board))
				{
					std::cout << result	<< "\n";
					return 0;
				}
			}
		}
		guard_position = next_position;
	} while(guard_position != starting_position);
	std::cout << result	<< "\n";
}

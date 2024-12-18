#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>

enum class Direction
{
    north = 1, east=1, south=-1, west=-1
};

struct Position
{
    int x, y;
    Direction direction = Direction::north;

    bool operator==(const Position& rhs) const
    {
        return x == rhs.x && y == rhs.y;
    }
    bool operator!=(const Position&) const = default;
};

namespace std 
{
    template <>
    struct hash<Position> 
    {
        size_t operator()(const Position& key) const 
        {
            size_t h1 = std::hash<int>{}(key.x);
            size_t h2 = std::hash<int>{}(key.y);
            return h1 ^ (h2 << 1);
        }
    };
}

Position move(Position guard_position)
{
    if(guard_position.direction == Direction::north || guard_position.direction == Direction::south)
        guard_position.y += static_cast<int>(guard_position.direction);
    else
        guard_position.x += static_cast<int>(guard_position.direction);
    return guard_position;
}

Position turn(Position position)
{
    if(position.direction == Direction::north)
        position.direction = Direction::east;
    else if(position.direction == Direction::east)
        position.direction = Direction::south;
    else if (position.direction == Direction::south)
        position.direction = Direction::west;
    else if (position.direction == Direction::west)
        position.direction = Direction::north;
    return position;
}

bool valid_position(const Position& position, const auto& board)
{
    return position.x > -1 && position.x < board[0].size() && position.y > -1 && position.y < board.size();
}

int main()
{
    Position guard_position{}, starting_position;
    std::unordered_set<Position> visited{};
    long long result{0};
    std::vector<std::vector<bool>> board{};
    std::ifstream in("6.in");
    std::string line;
    for(std::size_t y{0}; getline(in, line); ++y)
    {
        std::vector<bool> row{};
        for(std::size_t x{0}; x < line.size(); ++x)
        {
            if(line[x] == '^')
            {
                guard_position.x = x;
                guard_position.y = y;
                row.push_back(false);
            }
            if(line[x] == '.')
                row.push_back(false);
            else
                row.push_back(true);
        }
        board.push_back(row);
    }

    starting_position = guard_position;
    do
    {
        if(!visited.contains(guard_position))
        {
            ++result;
            visited.insert({guard_position.x, guard_position.y});
        }

        Position next_position = move(guard_position);
        for(int i{0}; i<4; ++i)
        {
            if(!valid_position(next_position, board))
            {
                std::cout << result << "\n";
                return 0;
            }
            else if(board[next_position.x][next_position.y] == true)
            {
                guard_position = turn(next_position);
                next_position = move(guard_position);
            }
        }
        guard_position = next_position;
    } while(guard_position != starting_position);
    std::cout << result << "\n";
}
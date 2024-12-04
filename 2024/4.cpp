#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>

unsigned long long explore_straight(const std::vector<std::string>& input, int x, int y)
{
    unsigned long long result{0};
    std::string to_find = "XMAS";
    std::unordered_map<std::string, std::string> current_found = {
        {"up", ""}, {"down", ""}, {"left", ""}, {"right", ""}
    };
    auto advance = [&](std::string direction, int new_x, int new_y) 
    {
        current_found[direction] += input[new_y][new_x];
        if(current_found[direction] == to_find)
            ++result;
    };
    for(int offset{0}; offset<4; ++offset)
    {
        if(x+offset < input[0].size())
            advance("right", x+offset, y);
        if(x-offset >= 0)
            advance("left", x-offset, y); 
        if(y+offset < input.size())
            advance("up", x, y+offset);
        if(y-offset >= 0)
            advance("down", x, y-offset);
    }
    return result;
}

unsigned long long explore_diagonals(const std::vector<std::string>& input, int x, int y)
{
    unsigned long long result{0};
    std::string to_find = "XMAS";
    std::unordered_map<std::string, std::string> current_found = {
        {"topleft", ""}, {"topright", ""}, {"bottomleft", ""}, {"bottomright", ""}
    };
    auto advance = [&](std::string direction, int new_x, int new_y)
    {
        current_found[direction] += input[new_y][new_x];
        if(current_found[direction] == to_find)
            ++result;
    };
    for(int offset{0}; offset<4; ++offset)
    {
        if(x+offset < input[0].size())
        {
            if(y+offset < input.size())
                advance("topright", x+offset, y+offset);
            if(y-offset >= 0)
                advance("bottomright", x-offset, y-offset);
        }
        if(x-offset >= 0)
        {
            if(y+offset < input.size())
                advance("topleft", x-offset, y+offset);
            if(y-offset >= 0)
                advance("bottomleft", x-offset, y-offset);
        }
    }
    return result;
}

int main()
{

    std::ifstream in("4.in");
    std::vector<std::string> input;
    std::string line;
    unsigned long long result{0};
    while(getline(in, line))
        input.push_back(line);
    for(int y{0}; y<input.size(); ++y)
    {
        for(int x{0}; x<input[0].size(); ++x)
        {
            if(input[y][x] == 'X')
                result += explore_straight(input, x, y) + explore_diagonals(input, x, y);
        }
    }
    std::cout << result << "\n";
}
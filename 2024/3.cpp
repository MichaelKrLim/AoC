#include <iostream>
#include <fstream>
#include <string>

int get_num(std::string input, int i)
{
    auto index{i-1};
    while(isdigit(input[++index]))
    return std::stoi(input.substr(i, index-i));
}

int resolve_input(std::string input)
{
    static long long result{};
    for(int i{0}; i<input.size()-1; ++i)
    {
        if(input.substr(i, 4) == 'mul(')
        {
            
        }
    }
    return result;
}

int main()
{
    std::string input;
    std::cin >> input;
    long long result = resolve_input(input);
    std::cout << result << "\n";
}
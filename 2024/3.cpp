#include <iostream>
#include <regex>
#include <fstream>
#include <string>

int main()
{
    std::fstream in("3.in");
    std::string input;
    std::string line{};
    while(std::getline(in, line)) 
    {
        input += line;
    }
    long long result{0};
    std::regex regx("mul\\(\\d{1,3},\\d{1,3}\\)");
    for(std::sregex_iterator rit(input.begin(), input.end(), regx), rend; rit != rend; ++rit) 
    {
        std::string operation = rit->str().substr(4, rit->str().size()-5);
        std::stringstream ss(operation);
        std::string lhs, rhs;
        getline(ss, lhs, ',');
        getline(ss, rhs, ',');
        result += std::stoi(lhs)*std::stoi(rhs);
    }
    std::cout << result << "\n";
}
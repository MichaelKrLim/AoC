#include <iostream>
#include <regex>
#include <fstream>
#include <string>
#include <sstream>

int main()
{
    std::ifstream in("3.in");
    std::ostringstream buffer;
    buffer << in.rdbuf();
    std::string input = buffer.str();
    unsigned long long result{0};
    std::regex regx("mul\\(\\d{1,3},\\d{1,3}\\)|don't\\(\\)|do\\(\\)");
    bool disabled{false};
    for(std::sregex_iterator rit(input.begin(), input.end(), regx); rit != std::sregex_iterator(); ++rit) 
    {
        std::string raw_match = rit->str();
        if(raw_match == "do()")
            disabled = false;
        if(raw_match == "don't()")
            disabled = true;
        if(raw_match[0] == 'm' && !disabled)
        {
            std::string operation = raw_match.substr(4, rit->str().size()-5);
            std::stringstream ss(operation);
            std::string lhs, rhs;
            getline(ss, lhs, ',');
            getline(ss, rhs, ',');
            result += std::stoull(lhs)*std::stoull(rhs);
        }
    }
    std::cout << result << "\n";
}
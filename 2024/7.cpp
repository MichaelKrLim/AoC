#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

enum class Operand
{
    addition, multiplication, concatenation
};

unsigned long long evaluate(const auto& numbers, const auto& operators)
{
    unsigned long long result{numbers[0]};
    for(int i{0}; i<operators.size(); ++i)
    {
        switch(operators[i])
        {
            case Operand::multiplication:
                result *= numbers[i+1];
            break;
            case Operand::addition:
                result += numbers[i+1];
            break;
            case Operand::concatenation:
                result = std::stoll(std::to_string(result) + std::to_string(numbers[i + 1]));
            break;
        }
    }
    return result;
}

//who need dp?
bool is_valid(const auto& target, const auto& numbers, auto operators)
{
    auto current_evaluation = evaluate(numbers, operators);
    if(current_evaluation > target)
        return false;
    if(operators.size() == numbers.size()-1)
        return current_evaluation == target;
    
    operators.push_back(Operand::addition);
    bool a = is_valid(target, numbers, operators);
    operators.pop_back();
    operators.push_back(Operand::multiplication);
    bool b = is_valid(target,numbers,operators);
    operators.pop_back();
    operators.push_back(Operand::concatenation);
    return a || b || is_valid(target, numbers, operators);
}

int main()
{
    std::ifstream in("7.in");
    std::string line{};
    unsigned long long result{0};
    while(getline(in, line))
    {
        std::istringstream iss(line);
        unsigned long long target;
        char c;
        iss >> target >> c >> std::ws;
        std::string number{};
        std::vector<int> numbers{};
        while(getline(iss, number, ' '))
        {
            numbers.push_back(std::stoi(number));
        }
        if(is_valid(target, numbers, std::vector<Operand>{}))
            result += target;
    }
    std::cout << result << "\n";
}
#include <array>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <ranges>
#include <queue>
#include <string>
#include <set>
#include <ranges>
#include <unordered_map>


std::vector<int> correct_update(auto pq, auto update_frequencies)
{
    std::vector<int> corrected_list{};
    while(!pq.empty())
    {
        const auto current_value = pq.top();
        pq.pop();
        for(; update_frequencies[current_value] > 0; --update_frequencies[current_value])
        {
            corrected_list.push_back(current_value);
        }
    }
    return corrected_list;
}

int main()
{
    unsigned long long result{0};
    std::ifstream in("5.in");
    std::string line{};
    std::array<int, 100> priority{};
    while(getline(in, line))
    {
        if(line == "")
            break;
        std::istringstream iss(line);
        int higher;
        char c;
        iss >> higher;
        ++priority[higher];
    }
    auto cmp = [&](const auto& lhs, const auto& rhs)
    {
        return priority[rhs]>priority[lhs];
    };
    std::priority_queue<int, std::vector<int>, decltype(cmp)> pq{cmp};
    for(int i{0}; i<100; ++i)
    {
        pq.push(i);
    }

    std::vector<std::array<int, 100>> updates_frequencies{};
    for(int i{0}; getline(in, line); ++i)
    {
        updates_frequencies.push_back({});
        std::istringstream iss(line);
        std::string digit;
        while(getline(iss, digit, ','))
            ++updates_frequencies[i][std::stoi(digit)];
    }

    for(auto& update_frequencies : updates_frequencies)
    {
        const std::vector<int> corrected_update = correct_update(pq, update_frequencies);
        if(!corrected_update.empty())
            result += corrected_update[corrected_update.size()/2];
    }
    std::cout << result << "\n";
}
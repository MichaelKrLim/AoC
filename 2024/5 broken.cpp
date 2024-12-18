#include <array>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <ranges>
#include <queue>
#include <string>
#include <ranges>


std::vector<int> correct_update(auto priorities, auto update_frequencies)
{
    std::vector<int> corrected_list{};
    for(int i{0}; i<priorities.size(); ++i)
    {
        const int page = priorities[i].page;
        for(; update_frequencies[page] > 0; --update_frequencies[page])
        {
            corrected_list.push_back(page);
        }
    }
    return corrected_list;
}

int main()
{
    struct Priority
    {
        int page, priority{0};
        Priority(int page) : page(page) {};
    };
    unsigned long long result{0};
    std::ifstream in("5.in");
    std::string line{};
    std::vector<Priority> priorities;
    int page{0};
    std::generate_n(std::back_inserter(priorities), 100, [&page] { return Priority(page++); });
    while(getline(in, line))
    {
        if(line == "")
            break;
        std::istringstream iss(line);
        int higher;
        char c;
        iss >> higher;
        ++priorities[higher].priority;
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

    std::ranges::sort(priorities, [](const auto& lhs, const auto& rhs){return lhs.priority > rhs.priority;});
    for(auto& update_frequencies : updates_frequencies)
    {
        const std::vector<int> corrected_update = correct_update(priorities, update_frequencies);
        if(!corrected_update.empty())
            result += corrected_update[corrected_update.size()/2];
    }
    std::cout << result << "\n";
}
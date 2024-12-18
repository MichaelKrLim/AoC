#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <ranges>

struct data
{
    int ID{}, freq{};
};

long long checksum(const std::vector<data>& defragmented)
{
    long long result{0};
    std::size_t position{0};
    for(std::size_t i{0}; i<defragmented.size(); ++i)
    {
        if(defragmented[i].ID > -1)
        {
            for(std::size_t j{0}; j<defragmented[i].freq; ++j)
            {
                result += defragmented[i].ID * position;
                ++position;
            }
        }
        else
            position += defragmented[i].freq;
    }
    return result;
}

int main()
{
    std::ifstream in("9.in");
    std::string input;
    in >> input;
    std::vector<data> disk_map{};
    int ID{0};
    for(std::size_t i{0}; i<input.size(); ++i)
    {
        const auto current = input[i]-'0';
        if(i%2==0)
        {
            disk_map.push_back({ID, current});
            ++ID;
        }
        else
            disk_map.push_back({-1, current});
    }

    std::vector<data> defragmented{};
    for(std::size_t i{0}; i<disk_map.size(); ++i)
    {
        auto current = disk_map[i];
        if(current.ID < 0)
        {
            data to_insert{};
            do
            {
                to_insert = {-1, -1};
                for(int j{disk_map.size()-1}; j>-1 && j>i; --j)
                {
                    if(disk_map[j].ID > 0 && disk_map[j].freq <= current.freq && disk_map[j].ID > to_insert.ID)
                    {
                        to_insert = disk_map[j];
                    }
                }
                if(to_insert.ID > 0);
                    disk_map.erase(std::remove_if(disk_map.begin(), disk_map.end(), [&](const auto& d){ return to_insert.ID==d.ID; }), disk_map.end());
                defragmented.push_back(to_insert);
                current.freq -= to_insert.freq;
            } while(current.freq > 0 && to_insert.ID != -1);
            if(current.freq > 0)
                defragmented.push_back({-1, current.freq});
        }
        else
            defragmented.push_back(current);
    }
    std::cout << checksum(defragmented) << "\n";
}
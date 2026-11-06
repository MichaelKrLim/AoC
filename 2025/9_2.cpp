#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

struct Position
{
	long long x, y;

	bool operator==(const Position& rhs) const=default;
};

struct Interval
{
	long long start, end;
};

int main()
{
	std::ifstream input{"9_2.in"};
	std::vector<Position> red_tiles;
	for(std::string line{""}; std::getline(input,line);)
	{
		Position current;
		char comma;
		std::istringstream iss{line};
		iss>>current.x>>comma>>current.y;
		red_tiles.push_back(current);
	}

	std::unordered_map<long long, Interval> y_walls, x_walls;

	std::ranges::sort(red_tiles,std::less<>{},[](const Position& position){ return position.y; });
	for(auto it{red_tiles.begin()}; it!=red_tiles.end();)
	{
		auto end_it{std::ranges::upper_bound(it,red_tiles.end(),it->y,std::less<>{},[](const Position& position){ return position.y; })};
		y_walls[it->y]=Interval{it->x,(end_it-1)->x};
		it=end_it;
	}

	std::ranges::sort(red_tiles,std::less<>{},[](const Position& position){ return position.x; });
	for(auto it{red_tiles.begin()}; it!=red_tiles.end();)
	{
		auto end_it{std::ranges::upper_bound(it,red_tiles.end(),it->x,std::less<>{},[](const Position& position){ return position.x; })};
		x_walls[it->x]=Interval{it->y,(end_it-1)->y};
		it=end_it;
	}

	unsigned long long max_area{0};
	for(std::size_t i{0}; i<red_tiles.size()-1; ++i)
	{
		for(std::size_t j{i+1}; j<red_tiles.size(); ++j)
		{
			Position o1{red_tiles[i].x,red_tiles[j].y},o2{red_tiles[j].x,red_tiles[i].y};

			if(!std::ranges::all_of(std::array{o1,o2}, [&](const Position& position)
			{
				if(const auto it{std::ranges::find(red_tiles,position)}; it!=red_tiles.end())
					return true;
				if(const auto it{x_walls.find(position.x)}; it!=x_walls.end() && position.y>=it->second.start && position.y<=it->second.end)
					return true;
				return y_walls.contains(position.y) && position.x>=y_walls[position.y].start && position.x<=y_walls[position.y].end;
			}))
				continue;
			
			long long width=std::abs(red_tiles[i].x-red_tiles[j].x)+1, height=std::abs(red_tiles[i].y-red_tiles[j].y)+1;
			if(const long long area{width*height}; area>max_area)
				max_area=area;
		}
	}
	
	std::cout<<max_area<<"\n";
}

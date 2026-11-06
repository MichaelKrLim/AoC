#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

struct Position { long long x, y;       };
struct Interval { long long start, end; };

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

	Position previous{red_tiles.back()};
	std::unordered_map<long long, std::vector<Interval>> x_intervals, y_intervals;
	for(std::size_t i{0}; i<red_tiles.size(); ++i)
	{
		if(previous.x==red_tiles[i].x)
			x_intervals[previous.x].emplace_back(Interval{std::min(previous.y,red_tiles[i].y),std::max(previous.y,red_tiles[i].y)});
		else if(previous.y==red_tiles[i].y)
			y_intervals[previous.y].emplace_back(Interval{std::min(previous.x,red_tiles[i].x),std::max(previous.x,red_tiles[i].x)});
		else
			std::unreachable();

		previous=red_tiles[i];
	}

	unsigned long long max_area{0};
	for(std::size_t i{0}; i<red_tiles.size()-1; ++i)
	{
		for(std::size_t j{i+1}; j<red_tiles.size(); ++j)
		{
			Position vertex_one{red_tiles[i].x,red_tiles[j].y}, vertex_two{red_tiles[j].x,red_tiles[i].y};
			if([&]()
			{
				const Position top_right{std::max(red_tiles[i].x,red_tiles[j].x),std::max(red_tiles[i].y,red_tiles[j].y)};
				const Position bottom_left{std::min(red_tiles[i].x,red_tiles[j].x),std::min(red_tiles[i].y,red_tiles[j].y)};
				for(Position current_position{bottom_left.x+1,top_right.y}; current_position.x<top_right.x; ++current_position.x)
				{
					if(auto it{x_intervals.find(current_position.x)}; it!=x_intervals.end())
					{
						for(const Interval& interval : it->second)
						{
							if(current_position.y>interval.start && current_position.y<=interval.end)
								return true;
						}
					}
				}

				for(Position current_position{bottom_left.x+1,bottom_left.y}; current_position.x<top_right.x; ++current_position.x)
				{
					if(auto it{x_intervals.find(current_position.x)}; it!=x_intervals.end())
					{
						for(const Interval& interval : it->second)
						{
							if(current_position.y>=interval.start && current_position.y<interval.end)
								return true;
						}
					}
				}

				for(Position current_position{bottom_left.x,bottom_left.y+1}; current_position.y<top_right.y; ++current_position.y)
				{
					if(auto it{y_intervals.find(current_position.y)}; it!=y_intervals.end())
					{
						for(const Interval& interval : it->second)
						{
							if(current_position.x>=interval.start && current_position.x<interval.end)
								return true;
						}
					}
				}

				for(Position current_position{top_right.x,bottom_left.y+1}; current_position.y<top_right.y; ++current_position.y)
				{
					if(auto it{y_intervals.find(current_position.y)}; it!=y_intervals.end())
					{
						for(const Interval& interval : it->second)
						{
							if(current_position.x>interval.start && current_position.x<=interval.end)
								return true;
						}
					}
				}

				return false;
			}())
				continue;
			
			long long width=std::abs(red_tiles[i].x-red_tiles[j].x)+1, height=std::abs(red_tiles[i].y-red_tiles[j].y)+1;
			if(const long long area{width*height}; area>max_area)
				max_area=area;
		}
	}
	
	std::cout<<max_area<<"\n";
}

#include <algorithm>
#include <iostream>
#include <iterator>
#include <ranges>
#include <unordered_set>
#include <vector>

struct Position
{
	long long x,y,z;
};

std::istream& operator>>(std::istream& is, Position& position)
{
	char comma;
	return is>>position.x>>comma>>position.y>>comma>>position.z;
}

int main()
{
	std::vector<Position> boxes{std::istream_iterator<Position>{std::cin},{}};

	struct Distanced_box
	{
		long long distanced_from_index, closest_to_index, distance;
	};
	std::vector<Distanced_box> min_distance;
	const auto squared_distance=[](const Position& p1, const Position& p2)
	{
		const auto del_x{std::abs(p1.x-p2.x)},del_y{std::abs(p1.y-p2.y)},del_z{std::abs(p1.z-p2.z)};
		return del_x*del_x+del_y*del_y+del_z*del_z;
	};

	for(int i{0}; i<boxes.size(); ++i)
	{
		for(int j{i+1}; j<boxes.size(); ++j)
		{
			min_distance.push_back(Distanced_box{i,j,squared_distance(boxes[i],boxes[j])});
		}
	}

	std::vector<std::unordered_set<long long>> groups;
	for(long long i{0}; i<boxes.size(); ++i)
		groups.push_back(std::unordered_set{i});
	std::ranges::sort(min_distance,std::less<>{},&Distanced_box::distance);
	for(auto& [from_box_index, to_box_index, _] : min_distance | std::views::take(1000))
	{
		std::cout<<from_box_index<<' '<<to_box_index<<"\n";
		auto group_containing_from_box{std::ranges::find_if(groups, [&](const std::unordered_set<long long>& group)
		{
			return group.contains(from_box_index);
		})}, closest_group{std::ranges::find_if(groups, [&](const std::unordered_set<long long>& group)
		{
			return group.contains(to_box_index);
		})};

		if(closest_group!=group_containing_from_box)
		{
			group_containing_from_box->insert(closest_group->begin(), closest_group->end());
			groups.erase(closest_group);
		}
	}
	const auto to_size=[](const auto& group){ return group.size(); };
	std::ranges::sort(groups,std::greater<>{},to_size);

	std::ranges::copy(groups | std::views::transform(to_size) | std::views::take(3), std::ostream_iterator<long long>{std::cout,","});
	std::cout<<"\n";
	std::cout<<std::ranges::fold_left(groups | std::views::transform(to_size) | std::views::take(3), 1ull, std::multiplies<>{});
}

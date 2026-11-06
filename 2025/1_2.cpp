#include <bits/stdc++.h>

int main()
{
	std::ifstream input{"1_2.in"};
	int total{50}, result{0};
	for(std::string word{""}; std::getline(input, word);)
	{
		const int num{std::stoi(word.substr(1))};
		if(word[0]=='R')
		{
			for(int i{0}; i<num; ++i)
			{
				total=(total+1)%100;
				if(total==0)
					++result;
			}
		}
		if(word[0]=='L')
		{
			for(int i{0}; i<num; ++i)
			{
				--total;
				if(total<0)
					total=99;
				if(total==0)
					++result;
			}
		}
	}
	std::cout<<result<<"\n";
}

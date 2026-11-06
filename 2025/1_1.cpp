#include <bits/stdc++.h>

int main()
{
	std::ifstream input{"1_1.in"};
	int total{50}, result{0};
	for(std::string word{""}; std::getline(input, word);)
	{
		const int num{std::stoi(word.substr(1))};
		if(word[0]=='R')
			total=(total+num)%100;
		if(word[0]=='L')
			total=(total+(100-num))%100;

		if(total==0)
			++result;
	}
	std::cout<<result<<"\n";
}

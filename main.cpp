
#include <iostream>
#include <iomanip>
#include <vector>
#include <chrono>
#include <iterator>
#include <functional>
#include <algorithm>
#include <fstream>
#include <random>

#include "generators.h"
#include "countsort.h"

// Отсюда
// https://stackoverflow.com/a/21995693
template<typename TimeT = std::chrono::milliseconds>
struct measure
{
	// typedef typename TimeT::rep type;
	using type = typename TimeT::rep;

	template<typename F, typename ...Args>
	static typename TimeT::rep execution(F&& func, Args&&... args)
	{
		auto start = std::chrono::steady_clock::now();
		std::forward<decltype(func)>(func)(std::forward<Args>(args)...);
		auto duration = std::chrono::duration_cast< TimeT>
							(std::chrono::steady_clock::now() - start);
		return duration.count();
	}
};



int main(int argc, char const *argv[])
{

	std::vector<int> v;

	std::random_device rd;
	std::mt19937 g(rd());
	std::uniform_int_distribution<int> dist(0, 3);
	for(int i=0; i<20; i++)
	{
		v.push_back(dist(rd));
	}

	std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;

	auto res = std::move(otusalg::cntsort(4, v));
	
	std::copy(res.begin(), res.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;


	std::vector<int> gen;
	otusalg::gen_type2(10000000, gen);

	v.clear();
	std::copy(gen.begin(), gen.end(), std::back_inserter(v));
	std::cout << "Radix sort \n";
	std::cout << measure<std::chrono::microseconds>::execution([&]()
		{
			otusalg::radixsort(v);
		}) << " us\n";
	if(std::is_sorted(v.begin(), v.end(), std::less<int>())) std::cout << "vector sorted\n";
	else std::cout << "vector NOT sorted\n";
	std::cout << std::endl;


	v.clear();
	std::copy(gen.begin(), gen.end(), std::back_inserter(v));
	std::cout << "std::sort \n";
	std::cout << measure<std::chrono::microseconds>::execution([&]()
		{
			std::sort(v.begin(), v.end(), std::less<int>());
		}) << " us\n";
	if(std::is_sorted(v.begin(), v.end(), std::less<int>())) std::cout << "vector sorted\n";
	else std::cout << "vector NOT sorted\n";
	std::cout << std::endl;


	return 0;
}


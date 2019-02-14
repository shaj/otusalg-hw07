
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

	otusalg::gen_type8(20, v, 0, 3);

	std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;

	auto res = std::move(otusalg::cntsort(4, v));
	
	std::copy(res.begin(), res.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;


	const std::vector<std::pair<int, int>> test {{0, 0x7fffffff}, {240, 250}, {250, 260}, {0, 15}, {0, 16}};
	// const std::vector<std::pair<int, int>> test 
	// {
	// 	{0, 1}, 
	// 	{0, 2}, 
	// 	{0, 3}, 
	// 	{0, 4}, 
	// 	{0, 5}, 
	// 	{0, 6}, 
	// 	{0, 7}, 
	// 	{0, 8}, 
	// 	{0, 9}, 
	// 	{0, 10}, 
	// 	{0, 11}, 
	// 	{0, 12}, 
	// 	{0, 13}, 
	// 	{0, 14}, 
	// 	{0, 15}, 
	// 	{0, 16}, 
	// 	{0, 17}, 
	// 	{0, 18}, 
	// 	{0, 19}, 
	// 	{0, 20}, 
	// 	{0, 21}, 
	// };
	std::vector<int> gen;
	for(const auto &dist: test)
	{
		std::cout << "\nDistribution [" << dist.first << ", " << dist.second << "]\n";
		otusalg::gen_type8(10000000, gen, dist.first, dist.second);

		v.clear();
		std::copy(gen.begin(), gen.end(), std::back_inserter(v));
		std::cout << "Radix sort 2\n";
		std::cout << measure<std::chrono::microseconds>::execution([&]()
			{
				otusalg::radixsort_2(v);
			}) << " us\n";
		if(!std::is_sorted(v.begin(), v.end(), std::less<int>())) std::cout << "vector NOT sorted\n";
		std::cout << std::endl;


		v.clear();
		std::copy(gen.begin(), gen.end(), std::back_inserter(v));
		std::cout << "std::sort \n";
		std::cout << measure<std::chrono::microseconds>::execution([&]()
			{
				std::sort(v.begin(), v.end(), std::less<int>());
			}) << " us\n";
		if(!std::is_sorted(v.begin(), v.end(), std::less<int>())) std::cout << "vector NOT sorted\n";
		std::cout << std::endl;
	}

	return 0;
}


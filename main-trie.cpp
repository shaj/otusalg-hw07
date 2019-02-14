
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
#include "trie.h"

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

	std::vector<unsigned short> v;

	// otusalg::gen_type8(20U, v, 0U, 3U);
	otusalg::gen_type2(5U, v);

	std::copy(v.begin(), v.end(), std::ostream_iterator<unsigned short>(std::cout, " "));
	std::cout << std::endl;

	otusalg::trie<unsigned short> tr(v);
	auto res = tr.get_sorted();
	
	std::copy(res.begin(), res.end(), std::ostream_iterator<unsigned short>(std::cout, " "));
	std::cout << std::endl;

	tr.print_trie(std::cout);


	// const std::vector<std::pair<int, int>> test {{0, 0x7fffffff}, {100, 110}, {100, 109}, {0, 10}, {0, 9}};
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
	// std::vector<int> gen;
	// for(const auto &dist: test)
	// {
	// 	std::cout << "\nDistribution [" << dist.first << ", " << dist.second << "]\n";
	// 	otusalg::gen_type8(1000000, gen, dist.first, dist.second);

	// }

	return 0;
}


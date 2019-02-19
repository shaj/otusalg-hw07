
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

	{

		std::vector<unsigned short> v { 0x1234, 0x2345, 0x3456, 0x1234, 0x2345, 0x3456 };

		std::cout << std::setbase(16) << std::showbase;
		std::copy(v.begin(), v.end(), std::ostream_iterator<unsigned short>(std::cout, " "));
		std::cout << std::endl;

		otusalg::trie<unsigned short> tr(v);
		auto res = tr.get_sorted();
		
		std::copy(res.begin(), res.end(), std::ostream_iterator<unsigned short>(std::cout, " "));
		std::cout << std::endl;

		tr.remove(0x2345);
		res = tr.get_sorted();
		std::copy(res.begin(), res.end(), std::ostream_iterator<unsigned short>(std::cout, " "));
		std::cout << std::endl;

		tr.remove(0x2345);
		res = tr.get_sorted();
		std::copy(res.begin(), res.end(), std::ostream_iterator<unsigned short>(std::cout, " "));
		std::cout << std::endl;

		tr.print_trie(std::cout);
	}


	{
		std::cout << "\n10 000 random values\n";
		std::vector<unsigned int> gen;
		std::vector<unsigned int> v1;

		otusalg::gen_type2(10000U, gen);

		std::copy(gen.begin(), gen.end(), std::back_inserter(v1));
		std::sort(v1.begin(), v1.end());

		otusalg::trie<unsigned int> tr(gen);
		auto v2 = tr.get_sorted();

		if(std::is_sorted(v2.begin(), v2.end()))
		{
			std::cout << "v2 is sorted\n";
			if(v2 == v1)
				std::cout << "v2 == v1\n";
			else
				std::cout << "v2 != v1\n";
		}
		else
			std::cout << "v2 is NOT sorted\n";
	}


	{
		std::cout << "\nMany duplicates\n";
		std::vector<unsigned int> gen;
		std::vector<unsigned int> v1;

		otusalg::gen_type8(10000U, gen, 100U, 150U);

		std::copy(gen.begin(), gen.end(), std::back_inserter(v1));
		std::sort(v1.begin(), v1.end());

		otusalg::trie<unsigned int> tr(gen);
		auto v2 = tr.get_sorted();

		if(std::is_sorted(v2.begin(), v2.end()))
		{
			std::cout << "v2 is sorted\n";
			if(v2 == v1)
				std::cout << "v2 == v1\n";
			else
				std::cout << "v2 != v1\n";
		}
		else
			std::cout << "v2 is NOT sorted\n";
	}

	return 0;
}


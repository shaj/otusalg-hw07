
#include <iostream>
#include <iomanip>
#include <vector>
#include <array>
#include <chrono>
#include <memory>
#include <algorithm>
#include <iterator>
#include <functional>
#include <fstream>

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

	using namespace std::placeholders;
	using restype=measure<std::chrono::microseconds>::type;

	// otusalg::print_gen_test(std::cout, 30);

	std::vector<int> v;

	func_vec[j](sizes[i], v);

	vres[i][j][0] = measure<std::chrono::microseconds>::execution([&]()
	{
		otusalg::sort(v.begin(), v.end(), std::less<int>());
	});
	if(!std::is_sorted(v.begin(), v.end(), std::less<int>())) std::cout << "vector NOT sorted [0] std::sort\n";



	return 0;
}


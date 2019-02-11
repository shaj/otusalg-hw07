
#pragma once

#include <vector>
#include <stdexcept>

namespace otusalg
{


/**
 * 
 */
template<typename T>
std::vector<T> cntsort(std::size_t maxval, std::vector<T> &v)
{
	static_assert(std::is_integral<T>::value, "Integral required.");

	std::vector<int> counters(maxval);
	for(const auto &it: v)
	{
		if((it < maxval) && (it >= 0)) counters[it]++;
		else throw std::out_of_range("Counting sort");
	}

	std::copy(counters.begin(), counters.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;

	int sum = 0;
	for(auto &it: counters)
	{
		sum += it;
		it = sum;
	}

	std::copy(counters.begin(), counters.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;

	std::vector<T> res(v.size());
	for(int i = v.size()-1; i>=0; --i)
	{
		// std::cout << " ~ i " << i << " v[i] " << v[i] << " counters[v[i]] " << counters[v[i]] << std::endl;
		counters[v[i]]--;
		res[counters[v[i]]] = v[i];
	}

	return res;
}


} // namespace otusalg


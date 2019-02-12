
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

	int sum = 0;
	for(auto &it: counters)
	{
		sum += it;
		it = sum;
	}

	std::vector<T> res(v.size());
	for(int i = v.size()-1; i>=0; --i)
	{
		counters[v[i]]--;
		res[counters[v[i]]] = v[i];
	}

	return res;
}

static constexpr unsigned long long int pow10[] = 
	{
		1UL,
		10UL,
		100UL,
		1000UL,
		10000UL,
		100000UL,
		1000000UL,
		10000000UL,
		100000000UL,
		1000000000UL,
		10000000000UL,
		100000000000UL,
		1000000000000UL,
		10000000000000UL,
		100000000000000UL,
		1000000000000000UL,
		10000000000000000UL,
		100000000000000000UL,
		1000000000000000000UL,
		10000000000000000000UL
	};

template<typename T>
bool cntsort_1(std::vector<T> &v, int digit)
{
	static_assert(std::is_integral<T>::value, "Integral required.");

	std::vector<int> counters(10);
	T tmp;

	for(const auto &it: v)
	{
		tmp = it % pow10[digit+1] / pow10[digit];
		counters[tmp]++;
	}

	int sum = 0;
	for(auto &it: counters)
	{
		sum += it;
		it = sum;
	}

	if(sum == counters[0]) return false;

	std::vector<T> res(v.begin(), v.end());
	for(int i = v.size()-1; i>=0; --i)
	{
		tmp = res[i] % pow10[digit+1] / pow10[digit];
		counters[tmp]--;
		v[counters[tmp]] = res[i];
	}

	return true;
}



template<typename T>
void radixsort(std::vector<T> &v)
{
	static_assert(std::is_integral<T>::value, "Integral required.");

	int digit = 0;
	while(cntsort_1(v, digit))
		digit++;
}

} // namespace otusalg


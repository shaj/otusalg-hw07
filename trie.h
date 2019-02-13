
#pragma once

#include <vector>
#include <stdexcept>
#include <memory>

namespace otusalg
{


static constexpr unsigned long long int pow16[] = 
	{
		0x000000000000000fUL,
		0x00000000000000f0UL,
		0x0000000000000f00UL,
		0x000000000000f000UL,
		0x00000000000f0000UL,
		0x0000000000f00000UL,
		0x000000000f000000UL,
		0x00000000f0000000UL,
		0x0000000f00000000UL,
		0x000000f000000000UL,
		0x00000f0000000000UL,
		0x0000f00000000000UL,
		0x000f000000000000UL,
		0x00f0000000000000UL,
		0x0f00000000000000UL,
		0xf000000000000000UL,
	};

static constexpr unsigned int pow16s[] = 
	{
		0,
		4,
		8,
		12,
		16,
		20,
		24,
		28,
		32,
		34,
		38,
		42,
		46,
		50,
		54,
		58,
		62
	};


template<typename T>
class trieItem
{
	static_assert(std::is_integral<T>::value, "Integral required.");
	static_assert(std::is_unsigned<T>::value, "Unsigned required.");

	static constexpr int trie_weight = sizeof(T) / 4;

	std::map<unsigned char, std::unique_ptr<trieItem>> branch;

public:
	trieItem() {}
	~trieItem() {}
	
	void add(T it, int depth)
	{
		unsigned char tmp = static_cast<unsigned char>((it & pow16[trie_weight - depth]) >> pow16s[trie_weight - depth]);
		T val = it ^ (it & pow16[trie_weight - depth]);
		auto res = branch.find(tmp);
		if(res == branch.end())
		{
			branch.add(tmp);
			branch[tmp] = std::make_unique<trieItem>();
		}

		branch[tmp].add(val, depth + 1);
	}

};


template<typename T>
class trie
{
	static_assert(std::is_integral<T>::value, "Integral required.");
	static_assert(std::is_unsigned<T>::value, "Unsigned required.");

	trieItem<T> rootItem;

public:

	trie(const std::vector<T> &v)
	{
		for(auto it: v) add(it);
	}


	~trie() {}
	
	void add(T it)
	{
		rootItem.add(it, 0);
	}


};

} // namespace otusalg


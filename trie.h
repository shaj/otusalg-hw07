
#pragma once

#include <vector>
#include <map>
#include <stdexcept>
#include <memory>

#include <cstdio>

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

	static constexpr int trie_weight = sizeof(T) * 2;   // разряд 4 бита

	std::map<int, std::unique_ptr<trieItem>> branch;

	int nodeId;

	int leaf_cnt;

public:
	trieItem() : nodeId(0), leaf_cnt(0) {}
	~trieItem() {}
	
	void add(T it, int depth)
	{
std::cout << __PRETTY_FUNCTION__ << std::endl;
std::cout << "   it: " << it << " depth: " << depth << "\n";

		int tmp = static_cast<int>((it & pow16[trie_weight - depth - 1]) >> pow16s[trie_weight - depth - 1]);
		T val = it ^ (it & pow16[trie_weight - depth]);

std::cout << "   tmp: " << tmp << " val: " << val << "\n";


		// Тут проверяем, что лист (последний регистр)
		if(depth == trie_weight - 1)
		{
			// branch.at(tmp)->add_leaf();
			add_leaf();
std::cout << "   LEAF\n";
		}
		else
		{
			auto res = branch.find(tmp);
			if(res == branch.end())
			{
				branch[tmp] = std::make_unique<trieItem<T>>();
			}
			branch.at(tmp)->add(val, depth + 1);
		}		
	}

	void add_leaf()
	{
		leaf_cnt++;
	}

	void get_sorted(std::vector<T> &v, T buf, int depth)
	{
		T tmp;
std::cout << __PRETTY_FUNCTION__ << std::endl;

		for(int i=0; i<leaf_cnt; i++)
			v.push_back(tmp);

		for(const auto &it: branch)
		{
			tmp = (it.first << pow16s[trie_weight - depth - 1]) | buf;
std::cout << "   it.first: " << it.first << " depth: " << depth << "\n";
std::cout << "   tmp: " << tmp << " buf: " << buf << "\n";
			it.second->get_sorted(v, tmp, depth + 1);
		}
	}


	void print(std::ostream &os)
	{
		os << "Trie node: ";
		for(const auto &it: branch) 
			os << static_cast<unsigned int>(it.first) << " ";
		os << "\n";
		for(const auto &it: branch)
			it.second->print(os);
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
std::cout << std::setbase(16) << std::showbase;
		rootItem.add(it, 0);
	}

	void remove(T it)
	{
	}

	std::vector<T> get_sorted()
	{
std::cout << __PRETTY_FUNCTION__ << std::endl;
std::cout << std::setbase(16) << std::showbase;
		std::vector<T> v;
		rootItem.get_sorted(v, 0, 0);
		return v;
	}

	void print_trie(std::ostream &os)
	{
		os << "Trie root\n";
std::cout << std::setbase(16) << std::showbase;
		rootItem.print(os);
	}

};

} // namespace otusalg


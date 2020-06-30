#pragma once
#include <string.h>
#include"List.h"

template <typename T>
void swap(T& L, T& R)
{
	T temp;

	if (sizeof(T) > 4)
	{
		memmove(&temp, &L, sizeof(T));
		memmove(&L, &R, sizeof(T));
		memmove(&R, &temp, sizeof(T));
	}
	else
	{
		temp= L;
		L = R;
		R = temp;
	}
}


template <typename T>
T partition(T begin, T end, int (*comparator)(typename T::Reference, typename T::Reference))
{
	auto par = begin;
	auto pivot = begin;

	//loop to get the pivot element(last one):
	for (auto it = begin; ++it != end; ++pivot);

	for (auto i = begin; i != pivot; ++i)
		if (comparator(*i, *pivot) != 1)
		{
			swap(*par, *i);
			++par;
		}
	swap(*pivot, *par);

	return par;
}

template <typename I>
void sort(I begin, I end, int (*comparator)(typename I::Reference, typename I::Reference))
{
	if(begin != end)
	{ 
		auto pivot = partition(begin, end,comparator);
			sort(begin,pivot, comparator);
			sort(++pivot, end, comparator);
	}
}

template <typename T>
T max(T first, T last) { // not including last
	if (first == last) return last;
	T iMax = first;
	for (++first; first != last; ++first)
		if (*iMax < *first)
			iMax = first;
	return iMax;
}




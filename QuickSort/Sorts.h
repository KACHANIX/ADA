#pragma once

#include <stack>

#define INSERTION_ELEMENTS 10
template<typename T>
void swap(T* a, T* b)
{
	T tmp = *a;
	*a = *b;
	*b = tmp;
}

template<typename T, typename Compare>
void StartSort(T* first, T* middle, T* last, Compare comp)
{// find median and put it in the middle
	if (!comp(*first, *middle))
	{
		swap(first, middle);
	}
	if (!comp(*first, *last))
	{
		swap(first, last);
	}
	if (!comp(*middle, *last))
	{
		swap(middle, last);
	}
}

template<typename T, typename Compare>
void InsertionSort(T* first, T* last, Compare comp)
{
	if (last == first)
	{
		return;
	} 
	for (int i = 1; i <= last - first; i++)
	{
		for (int j = i; j > 0; j--)
		{ 
			if (comp(*(first + j - 1), *(first + j)))
			{
				break;
			}
			swap((first + j - 1), (first + j));
		}
	}

} 

template<typename T, typename Compare>
T* Partition(T* first, T* pivot_element, T* last, Compare comp)
{
	StartSort(first, pivot_element, last, comp);
	if (first + 2 == last) return pivot_element; // there are only 3 elements, already sorted in StartSort

	swap(pivot_element, last - 1); // putting pivot next to the last element
	pivot_element = last - 1;
	int i = 1, j = last - first - 1;

	while (i < j)
	{
		while (comp(*(first + i), *pivot_element)) i++;
		while (!comp(*(first + j), *pivot_element)) j--;
		if (i <= j) swap(first + i, first + j);
	}
	if (first + i != pivot_element)
	{
		swap(first + i, pivot_element); // swap pivot and the first element bigger than it.
		//pivot_element = (first + i);
		return (first + i);
	}
	return pivot_element;
}

template<typename T, typename Compare>
void QSort(T* first, T* last, Compare comp)
{
	if (first == last) return; // if array has only 1 element
	if (last - first > INSERTION_ELEMENTS - 1)
	{
		T* pivot_element = Partition(first, (first + (last - first) / 2), last, comp);
		T* iter_first;
		T* iter_last;
		if (pivot_element + 1 == last && pivot_element - 1 == first) return;
		if (pivot_element - first <= last - pivot_element)
		{
			if (first != pivot_element - 1)
				QSort(first, pivot_element - 1, comp);
			iter_first = pivot_element + 1;
			iter_last = last;
		}
		else
		{
			if (pivot_element + 1 != last)
				QSort(pivot_element + 1, last, comp);
			iter_first = first;
			iter_last = pivot_element - 1;
		}

		//iterative qsort goes here
		std::stack<T*> stack;
		stack.push(iter_first);
		stack.push(iter_last);
		while (!stack.empty())
		{
			iter_last = stack.top(); stack.pop();
			iter_first = stack.top(); stack.pop();

			if (iter_last - iter_first > INSERTION_ELEMENTS - 1)
			{
				T* iter_pivot = Partition(iter_first, (iter_first + (iter_last - iter_first) / 2), iter_last, comp);
				if (iter_pivot - iter_first > 1)
				{
					stack.push(iter_first);
					stack.push(iter_pivot - 1);
				}
				if (iter_last - iter_pivot > 1)
				{
					stack.push(iter_pivot + 1);
					stack.push(iter_last);
				}
			}
			else
			{
				InsertionSort(iter_first, iter_last, comp);
			}
		}
	}
	else
	{
		InsertionSort(first, last, comp);
	}
}

//template <typename T>
//bool comp(const T& a, const T& b);

#include <chrono>
#include <iostream>
#include "Sorts.h"


int main()
{
	int iterations = 100000;
	long long  microseconds = 0;

	const int arr_len = 1000;
	int a[arr_len];

	for (int i = 0; i < iterations; i++)
	{
		for (int j = 0 ; j < arr_len;j++)
		{
			a[j] = arr_len - j;
		}
		auto start = std::chrono::high_resolution_clock::now();
		QSort(a, a + arr_len - 1, [](int a, int b) { return a < b; });
		auto finish = std::chrono::high_resolution_clock::now();
		microseconds += std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();
	}

	std::cout << microseconds / iterations << std::endl;

	/*

	for (const auto& e : a)
	{
		std::cout << e << " ";
	}*/

	//std::cout << *a << "	" << *(a + 9);
	std::cout << "Hello World!\n";
}
